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


namespace UnrealBuildTool.Rules
{
	public class CohtmlEditorPlugin : ModuleRules
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
		public CohtmlEditorPlugin(ReadOnlyTargetRules Target) : base(Target)
#else
		public CohtmlEditorPlugin(TargetInfo Target)
#endif
		{
			if (ReadEngineMajorVersion() == 4 && ReadEngineMinorVersion() >= 15)
			{
				bool bIsEngineModule = ModuleDirectory.Contains(
					System.IO.Path.Combine("Engine", "Plugins", "Runtime"));
				if(bIsEngineModule)
				{
					PCHUsage = PCHUsageMode.UseSharedPCHs;
					SharedPCHHeaderFile = "Private/CohtmlEditorPluginPrivatePCH.h";
				}
				else
				{
					PCHUsage = PCHUsageMode.NoSharedPCHs;
				}
			}
#if UE_4_21_OR_LATER
			PrivatePCHHeaderFile = "Private/CohtmlEditorPluginPrivatePCH.h";
#endif

#if UE_4_18_OR_LATER
			string CohtmlIncludeDir = Target.UEThirdPartySourceDirectory;
#else
			string CohtmlIncludeDir = UEBuildConfiguration.UEThirdPartySourceDirectory;
#endif

			CohtmlIncludeDir += "Cohtml/include/";

			if (!System.IO.Directory.Exists(CohtmlIncludeDir))
			{
				CohtmlIncludeDir = ModuleDirectory + "/../Cohtml/include";
			}

			PublicIncludePaths.AddRange(
				new string[] {
					// ... add public include paths required here ...
					CohtmlIncludeDir
				}
			);

			PrivateIncludePaths.AddRange(
				new string[] {
					"CohtmlEditorPlugin/Private",
					"CohtmlEditorPlugin/Classes",
				}
			);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"UnrealEd",
					"BlueprintGraph",
					"AssetTools",
					"Core",
					"CoreUObject",
					"InputCore",
					"Engine",
					"EngineSettings",
					"EditorStyle",
					"Kismet",
					"KismetCompiler",
					"KismetWidgets",
					"LevelEditor",
					"MainFrame",
					"PropertyEditor",
					"RenderCore",
					"RHI",
					"Slate",
					"SlateCore",
					"UnrealEd",
					"DirectoryWatcher",
					"ContentBrowser",
					"CohtmlPlugin",
					"ScreenshotComparisonTools",
					"CoherentRenderingPlugin",
#if !UE_4_22_OR_LATER
					"ShaderCore",
#endif
				}
			);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"Cohtml",
					"CohtmlEditorPlugin",
				}
			);

#if UE_4_24_OR_LATER
            bUseUnity = true;
#elif UE_4_18_OR_LATER
            bFasterWithoutUnity = false;
#endif
		}
	}
}
