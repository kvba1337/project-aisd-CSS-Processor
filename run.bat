@echo off
setlocal enabledelayedexpansion

:: Set paths
set SOURCE_DIR=src
set TEST_DIR=tests
set EXECUTABLE=css_processor.exe

:: Compile
g++ -std=c++11 %SOURCE_DIR%\main.cpp %SOURCE_DIR%\data_structures\my_string.cpp %SOURCE_DIR%\utils\utils.cpp %SOURCE_DIR%\core\css_parser.cpp %SOURCE_DIR%\core\command_processor.cpp %SOURCE_DIR%\operations\query_functions.cpp %SOURCE_DIR%\operations\delete_functions.cpp -o %EXECUTABLE%

if %ERRORLEVEL% neq 0 (
    echo Compilation failed!
    exit /b 1
)
echo Compilation successful!

:: Create temporary files
set TEMP_OUTPUT=temp_output.txt
set EXPECTED_LINES=expected_lines.txt
set ACTUAL_LINES=actual_lines.txt

:: Initialize counters
set PASSED=0
set FAILED=0
set TOTAL=0

:: Run each test
for /l %%i in (1, 1, 10) do (
    set TEST_NUM=%%i
    set INPUT_FILE=%TEST_DIR%\!TEST_NUM!.in
    set OUTPUT_FILE=%TEST_DIR%\!TEST_NUM!.out

    if not exist !INPUT_FILE! (
        echo Test !TEST_NUM!: Input file !INPUT_FILE! not found!
        continue
    )

    if not exist !OUTPUT_FILE! (
        echo Test !TEST_NUM!: Expected output file !OUTPUT_FILE! not found!
        continue
    )

    %EXECUTABLE% < !INPUT_FILE! > %TEMP_OUTPUT%

    fc %TEMP_OUTPUT% !OUTPUT_FILE! > nul
    if !ERRORLEVEL! equ 0 (
        echo Test !TEST_NUM!: PASSED
        set /a PASSED+=1
    ) else (
        echo Test !TEST_NUM!: FAILED

        if exist %EXPECTED_LINES% del %EXPECTED_LINES%
        if exist %ACTUAL_LINES% del %ACTUAL_LINES%

        for /f "tokens=*" %%a in (!OUTPUT_FILE!) do (
            echo %%a>> %EXPECTED_LINES%
        )

        for /f "tokens=*" %%a in (%TEMP_OUTPUT%) do (
            echo %%a>> %ACTUAL_LINES%
        )

        set /a expectedLines=0
        for /f %%a in ('type %EXPECTED_LINES% ^| find /c /v ""') do set expectedLines=%%a

        set /a actualLines=0
        for /f %%a in ('type %ACTUAL_LINES% ^| find /c /v ""') do set actualLines=%%a

        echo.
        echo Differences in Test !TEST_NUM!:

        set /a maxLines=!expectedLines!
        if !actualLines! GTR !expectedLines! set /a maxLines=!actualLines!

        for /l %%l in (1,1,!maxLines!) do (
            set "expectedLine="
            if %%l LEQ !expectedLines! (
                set /a lineNum=0
                for /f "usebackq tokens=*" %%a in (%EXPECTED_LINES%) do (
                    set /a lineNum+=1
                    if !lineNum!==%%l set "expectedLine=%%a"
                )
            )

            set "actualLine="
            if %%l LEQ !actualLines! (
                set /a lineNum=0
                for /f "usebackq tokens=*" %%a in (%ACTUAL_LINES%) do (
                    set /a lineNum+=1
                    if !lineNum!==%%l set "actualLine=%%a"
                )
            )

            if not "!expectedLine!"=="!actualLine!" (
                echo Line %%l:
                echo Expected: "!expectedLine!"
                echo Actual:   "!actualLine!"
                echo          ^<---- DIFFERENCE DETECTED

                set "expectedNum="
                set "actualNum="
                for /f "tokens=1" %%n in ("!expectedLine!") do set expectedNum=%%n
                for /f "tokens=1" %%n in ("!actualLine!") do set actualNum=%%n

                set "isExpectedNum=0"
                set "isActualNum=0"
                for /f "delims=0123456789" %%n in ("!expectedNum!") do if "%%n"=="" set isExpectedNum=1
                for /f "delims=0123456789" %%n in ("!actualNum!") do if "%%n"=="" set isActualNum=1

                if !isExpectedNum!==1 if !isActualNum!==1 (
                    set /a numDiff=expectedNum-actualNum
                    echo          Numeric difference: !numDiff!
                )

                echo.
            )
        )

        set /a FAILED+=1
    )
    set /a TOTAL+=1
)

:: Clean up temporary files
if exist %TEMP_OUTPUT% del %TEMP_OUTPUT%
if exist %EXPECTED_LINES% del %EXPECTED_LINES%
if exist %ACTUAL_LINES% del %ACTUAL_LINES%

:: Show results
echo.
echo Test results: !PASSED!/!TOTAL! tests passed
if !FAILED! gtr 0 (
    echo !FAILED! tests failed
    exit /b 1
) else (
    echo All tests passed!
    exit /b 0
)
