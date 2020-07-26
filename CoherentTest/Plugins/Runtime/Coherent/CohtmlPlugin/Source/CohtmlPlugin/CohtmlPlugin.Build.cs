/*
This file is part of Cohtml, modern user interface library for
games.

Copyright (c) 2012-2018 Coherent Labs AD and/or its licensors. All
rights reserved in all media.

The coded instructions, statements, computer programs, and/or related
material (collectively the "Data") in these files contain confidential
and unpublished information proprietary Coherent Labs and/or its
licensors, which is protected by United States of America federal
copyright law and by international treaties.

This software or source code is supplied under the terms of a license
agreement and nondisclosure agreement with Coherent Labs Limited and may
not be copied, disclosed, or exploited except in accordance with the
terms of that agreement. The Data may not be disclosed or distributed to
third parties, in whole or in part, without the prior written consent of
Coherent Labs Limited.

COHERENT LABS MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS
SOURCE CODE FOR ANY PURPOSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER, ITS AFFILIATES,
PARENT COMPANIES, LICENSORS, SUPPLIERS, OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
ANY WAY OUT OF THE USE OR PERFORMANCE OF THIS SOFTWARE OR SOURCE CODE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

using System;
using System.IO;
using System.Text.RegularExpressions;
using System.Collections.Generic;

namespace UnrealBuildTool.Rules
{
    public class CohtmlPlugin : ModuleRules
    {
        private int ReadEngineMajorVersion()
        {
            string line;
            int Major = 0;

            System.IO.StreamReader file =
               new System.IO.StreamReader("Runtime/Launch/Resources/Version.h");

            while ((line = file.ReadLine()) != null)
            {
                if (line.StartsWith("#define ENGINE_MAJOR_VERSION"))
                {
                    file.Close();
                    return int.Parse(line.Split()[2]);
                }
            }

            file.Close();

            return Major;
        }

        private int ReadEngineMinorVersion()
        {
            string line;
            int Minor = 0;

            System.IO.StreamReader file =
               new System.IO.StreamReader("Runtime/Launch/Resources/Version.h");

            while ((line = file.ReadLine()) != null)
            {
                if (line.StartsWith("#define ENGINE_MINOR_VERSION"))
                {
                    file.Close();
                    return int.Parse(line.Split()[2]);
                }
            }

            file.Close();

            return Minor;
        }

#if WITH_FORWARDED_MODULE_RULES_CTOR
        public CohtmlPlugin(ReadOnlyTargetRules Target) : base(Target)
#else
        public CohtmlPlugin(TargetInfo Target)
#endif
        {
#if UE_4_23_OR_LATER
            string PlatformName = Target.Platform.ToString();
#else
            string PlatformName = Enum.GetName(typeof(UnrealTargetPlatform), Target.Platform);
#endif

#if UE_4_18_OR_LATER
            string UE4ThirdPartyBinaries = Target.UEThirdPartyBinariesDirectory;
            string UE4ThirdPartySource = Target.UEThirdPartySourceDirectory;
#else
            string UE4ThirdPartyBinaries = UEBuildConfiguration.UEThirdPartyBinariesDirectory;
            string UE4ThirdPartySource = UEBuildConfiguration.UEThirdPartySourceDirectory;
#endif

            if (PlatformName == "Quail")
            {
                PlatformName = "Stadia";
            }
            if (PlatformName == "DPX")
            {
                PublicDefinitions.Add("PLATFORM_DPX=1");
                PublicDefinitions.Add("__RILA__=1");
            }
            else
            {
                PublicDefinitions.Add("PLATFORM_DPX=0");
            }

            if (ReadEngineMajorVersion() == 4 && ReadEngineMinorVersion() >= 15)
            {
                bool bIsEngineModule = ModuleDirectory.Contains(
                    System.IO.Path.Combine("Engine", "Plugins", "Runtime"));
                if (bIsEngineModule)
                {
                    PCHUsage = PCHUsageMode.UseSharedPCHs;
                    SharedPCHHeaderFile = "Private/CohtmlPluginPrivatePCH.h";
                }
                else
                {
                    PCHUsage = PCHUsageMode.NoSharedPCHs;
                }
            }
#if UE_4_21_OR_LATER
            PrivatePCHHeaderFile = "Private/CohtmlPluginPrivatePCH.h";
#endif

            string RenoirIncludeDir = ModuleDirectory + "/../../../CoherentRenderingPlugin/Source/Renoir/include/";
            if (!Directory.Exists(RenoirIncludeDir))
            {
                RenoirIncludeDir = UE4ThirdPartySource + "Renoir/include/";
            }

            string CohtmlIncludeDir = ModuleDirectory + "/../Cohtml/include/";
            if (!Directory.Exists(CohtmlIncludeDir))
            {
                CohtmlIncludeDir = UE4ThirdPartySource + "Cohtml/include/";
            }

            PublicIncludePaths.AddRange(
                new string[] {
                    // ... add public include paths required here ...
                    CohtmlIncludeDir,
                    RenoirIncludeDir
                }
            );

            PrivateIncludePaths.AddRange(
                new string[] {
                    "CohtmlPlugin/Private",
                    "CohtmlPlugin/Classes",
                }
            );

            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "RenderCore",
                    "RHI",
                    "UMG",
#if !UE_4_22_OR_LATER
                    "ShaderCore",
#endif
                }
            );

            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    "SSL",
                    "HTTP",
                    "SlateCore",
                    "Slate",
                    "InputCore",
#if !UE_4_24_OR_LATER
                    "UtilityShaders",
#endif
                    "Cohtml",
                    "CoherentRenderingPlugin",
                }
            );

            List<String> extensionsToPackage = new List<String>();

            if (Target.Platform == UnrealTargetPlatform.Win64 ||
                Target.Platform == UnrealTargetPlatform.Win32 ||
                Target.Platform == UnrealTargetPlatform.XboxOne)
            {
                extensionsToPackage.Add("*.dll");
                extensionsToPackage.Add("*.dat");
            }
#if UE_4_20_OR_LATER
            else if (Target.IsInPlatformGroup(UnrealPlatformGroup.Unix))
#else
            else if (Target.Platform == UnrealTargetPlatform.Linux)
#endif
            {
                extensionsToPackage.Add("*.so");
                extensionsToPackage.Add("*.debug");
                extensionsToPackage.Add("*.so.53");
            }
            else if (Target.Platform == UnrealTargetPlatform.PS4)
            {
                extensionsToPackage.Add("*.prx");
                extensionsToPackage.Add("*.dat");
            }
            else if (PlatformName == "DPX")
            {
                extensionsToPackage.Add("*.prx");
                PlatformName = "PS5";
            }
            else if (Target.Platform == UnrealTargetPlatform.Switch)
            {
                extensionsToPackage.Add("*.nro");
                extensionsToPackage.Add("*.nrr");
                extensionsToPackage.Add("*.nrs");
                extensionsToPackage.Add("*.nso");
                extensionsToPackage.Add("*.nss");
                extensionsToPackage.Add("*.dat");
            }
            //UnrealTargetPlatform.UWP64 and UnrealTargetPlatform.UWP32 not present in non UWP UNREAL fork
            else if (PlatformName == "UWP32" ||
                     PlatformName == "UWP64")
            {
                extensionsToPackage.Add("*.dll");
            }
            else if (PlatformName == "Mac")
            {
                PlatformName = "MacOSX";
                extensionsToPackage.Add("*.dylib");
            }

            string sharedLibrariesLocation = Path.Combine(ModuleDirectory, "../../Binaries/Cohtml", PlatformName);
            if (!Directory.Exists(sharedLibrariesLocation))
            {
                sharedLibrariesLocation = UE4ThirdPartyBinaries + "/Cohtml/" + PlatformName;
            }
            if (!Directory.Exists(sharedLibrariesLocation))
            {
                // check under Engine/Source/ThirdParty/Cohtml/lib
                sharedLibrariesLocation = UE4ThirdPartySource + "/Cohtml/lib/" + PlatformName;
            }

            extensionsToPackage.ForEach(delegate (String extension)
            {
                foreach (string FilePath in Directory.EnumerateFiles(sharedLibrariesLocation, extension, SearchOption.TopDirectoryOnly))
                {
#if UE_4_21_OR_LATER
                    string SanitizedFilePath = Regex.Replace(FilePath, @"\\|/+", @"/");
                    if (Target.Platform == UnrealTargetPlatform.XboxOne ||
                        PlatformName == "Stadia")
                    {
                        // Retarget the files to be copied next to the executable.
                        // This way they will be properly loaded after deployed on the dev kit.
                        string TargetFilePath = "$(TargetOutputDir)/" + SanitizedFilePath.Substring(SanitizedFilePath.LastIndexOf("/") + 1);
                        RuntimeDependencies.Add(
                            TargetFilePath, SanitizedFilePath
                        );
                        continue;
                    }
#endif

                    RuntimeDependencies.Add(
#if UE_4_19_OR_LATER
                        FilePath
#else
                        new RuntimeDependency(FilePath)
#endif
                    );
                }
            });

            if (Target.Platform == UnrealTargetPlatform.Mac)
            {
                // Adding the Renoir dylib since Cohtml has a dependency on it
                // TODO: See if we can somehow move this to the Renoir/Rendering plugin and load this automatically
                string sharedRenoirLibraries = Path.Combine(ModuleDirectory, "../../Binaries/Renoir/", PlatformName);
                if (!Directory.Exists(sharedRenoirLibraries))
                {
                    sharedRenoirLibraries = UE4ThirdPartyBinaries + "/Renoir/" + PlatformName;
                }
                if (!Directory.Exists(sharedRenoirLibraries))
                {
                    sharedRenoirLibraries = UE4ThirdPartySource + "/Renoir/lib/" + PlatformName;
                }
                extensionsToPackage.ForEach(delegate (String extension)
                {
                    foreach (string FilePath in Directory.EnumerateFiles(sharedRenoirLibraries, extension, SearchOption.TopDirectoryOnly))
                    {
                        PublicDelayLoadDLLs.Add(FilePath);
                        RuntimeDependencies.Add(FilePath);
                    }
                });
            }

#if UE_4_24_OR_LATER
            bUseUnity = true;
#elif UE_4_18_OR_LATER
            bFasterWithoutUnity = false;
#endif
        }
    }
}
