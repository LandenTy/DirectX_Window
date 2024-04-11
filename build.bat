@echo off

for /F "tokens=1-4 delims=:.," %%a in ("%TIME%") do (
    set /A "startMs=((((%%a*60)+1%%b %% 100)*60)+1%%c %% 100)*100+1%%d %% 100"
)

if not exist build mkdir build

for /r src %%f in (*.cpp) do (
    echo Compiling %%f...
    g++ -o build\%%~nf.o %%f -c -std=c++11 -Wall -mwindows
)

if errorlevel 1 (
    echo Compilation failed!
) else (
    echo Linking object files...
    g++ -o build\build.exe build\*.o -luser32 -lgdi32 -ld3d9 -ld3dx9 -mwindows

    if errorlevel 1 (
        echo Linking failed!
    ) else (
        echo Compilation and linking successful! Output executable: build\build.exe

        echo Copying DLLs to build directory...
        xcopy /Y "src\include\*.dll" "build\"

        echo DLLs copied to build directory.
    )
)

for /F "tokens=1-4 delims=:.," %%a in ("%TIME%") do (
    set /A "endMs=((((%%a*60)+1%%b %% 100)*60)+1%%c %% 100)*100+1%%d %% 100"
)
set /A "buildTimeMs=endMs-startMs"
echo Build finished in[32m %buildTimeMs% ms[0m

pause
