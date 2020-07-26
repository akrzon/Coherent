@echo off
echo Running Cohtml post-build script.

rem Keep all the path computations without any quotes.
rem Quote all the paths just before executing a command with them.
rem The sets below strip the quotes of the arguments using % ~
set EngineDirectory=%~1
set ProjectDir=%~2
set PluginDir=%~3
set TargetPlatform=%~4

set PS4SourceDirectory=%EngineDirectory%\Binaries\ThirdParty\Cohtml\PS4
set PS4RenoirSourceDirectory=%EngineDirectory%\Binaries\ThirdParty\Renoir\PS4
set PS5SourceDirectory=%EngineDirectory%\Binaries\ThirdParty\Cohtml\PS5
set PS5RenoirSourceDirectory=%EngineDirectory%\Binaries\ThirdParty\Renoir\PS5
set XBOXSourceDirectory=%EngineDirectory%\Binaries\ThirdParty\Cohtml\XboxOne
set XBOXRenoirSourceDirectory=%EngineDirectory%\Binaries\ThirdParty\Renoir\XboxOne
set XBOXDestinationDirectory=%ProjectDir%\Binaries\XboxOne
set PS4FontsDirectory=%PS4SourceDirectory%\fonts
set PS5FontsDirectory=%PS5SourceDirectory%\fonts
set XboxFontsDirectory=%XBOXSourceDirectory%\fonts
set UE4ContentDirectory=%ProjectDir%\Content
set PS4DestinationDirectory=%ProjectDir%\Build\PS4\prx
set StagedBuildDirectoryPS4=%ProjectDir%\Saved\StagedBuilds\PS4\prx
set PS5DestinationDirectory=%ProjectDir%\Build\DPX\prx
set StagedBuildDirectoryPS5=%ProjectDir%\Saved\StagedBuilds\DPX\prx

rem Read the version from the file
set VersionHeader=%EngineDirectory%\Source\Runtime\Launch\Resources\Version.h
set "Minor=define ENGINE_MINOR_VERSION"
set "Patch=define ENGINE_PATCH_VERSION"

rem Get the minor version
rem Find the line containing the macro definition. Get the last symbols of the line
rem and assume they are the version number.
setlocal enabledelayedexpansion
for /f "delims=" %%l in ('type "%VersionHeader%"') do (
    set CurrentLine=%%l
    set ReplacedLine=!CurrentLine:%Minor%=!
    if not x!ReplacedLine!==x!CurrentLine! (
        set MinorVer=!CurrentLine:~-2!
        break
    )
)

rem Get the patch version
for /f "delims=" %%l in ('type "%VersionHeader%"') do (
    set CurrentLine=%%l
    set ReplacedLine=!CurrentLine:%Patch%=!
    if not x!ReplacedLine!==x!CurrentLine! (
        set PatchVer=!CurrentLine:~-1!
        break
    )
)

set Version=!MinorVer!!PatchVer!

rem TODO: Remove this once we know what UE4 is passing
echo EngineDirectory: "%EngineDirectory%"
echo ProjectDir: "%ProjectDir%"
echo PluginDir: "%PluginDir%"
echo TargetPlatform: "%TargetPlatform%"

set DisableCopyingSharedLibsRecursively=1
if "%TargetPlatform%" == "PS4" (
    if exist "%PS4SourceDirectory%" (
        call :CopyAndReportError "%PS4SourceDirectory%" "%PS4DestinationDirectory%" %DisableCopyingSharedLibsRecursively%
        call :CopyAndReportError "%PS4RenoirSourceDirectory%" "%PS4DestinationDirectory%" %DisableCopyingSharedLibsRecursively%
        call :CopyAndReportError "%PS4FontsDirectory%" "%UE4ContentDirectory%\Fonts"
    ) else (
        echo Could not find PS4 dependencies in "%PS4SourceDirectory%"
        exit /B 1
    )
)

if "%TargetPlatform%" == "DPX" (
    if exist "%PS5SourceDirectory%" (
        call :CopyAndReportError "%PS5SourceDirectory%" "%PS5DestinationDirectory%" %DisableCopyingSharedLibsRecursively%
        call :CopyAndReportError "%PS5RenoirSourceDirectory%" "%PS5DestinationDirectory%" %DisableCopyingSharedLibsRecursively%
        call :CopyAndReportError "%PS5FontsDirectory%" "%UE4ContentDirectory%\Fonts"
    ) else (
        echo Could not find PS5 dependencies in "%PS5SourceDirectory%"
        exit /B 1
    )
)

if "%TargetPlatform%" == "XboxOne" (
    if !Version! LSS 214 (
        if exist "%XBOXSourceDirectory%" (
            call :CopyAndReportError "%XBOXSourceDirectory%" "%XBOXDestinationDirectory%" %DisableCopyingSharedLibsRecursively%
            call :CopyAndReportError "%XBOXRenoirSourceDirectory%" "%XBOXDestinationDirectory%" %DisableCopyingSharedLibsRecursively%
            call :CopyAndReportError "%XboxFontsDirectory%" "%UE4ContentDirectory%\Fonts"
        ) else (
            echo Could not find XboxOne dependencies in "%XBOXSourceDirectory%"
            exit /B 1
        )
    ) else (
        echo Skipping post-build step for XboxOne as it's no longer required for UE 4.21+
    )
)

echo Cohtml post-build script done.

exit /b 0

:CopyAndReportError
set Src=%~1
set Dst=%~2
if "%3"=="" (
    set GoRecursive="/S"
) else (
    set GoRecursive=""
)

set ERRORLEVEL=0
robocopy "%Src%" "%Dst%" %GoRecursive% /NC /NS /NFL /NDL /NP /NJS

if %ERRORLEVEL% NEQ 0 (
    echo Cohtml failed to copy some files.
    echo This may cause problems when running the game or the inspector.
    echo Check whether the following directory is writable: "%Dst%"
)
exit /B 0
