@echo off
rem ------------------------------------------------------------
rem Skrypt: run_tests.bat
rem Automatyzuje testowanie --test <problem> <algorithm> <size> <density> <count> <outputFile>
rem ------------------------------------------------------------


set REPS=50
set OUT=resultsALL.txt

REM Define sets of test configurations
set PROBLEM=0 1
set ALGS=0
set SIZE=25 50 100 160 220 300 400
set DENSITY=25 50 99

 REM Remove old results file and add header line
if exist %OUT% del /f %OUT%
echo problem algorithm size density edges count avgTimeList avgTimeMatrix>>%OUT%

REM Path to the compiled exe
set EXE=cmake-build-debug\AIZO_grafs.exe


for %%P in (%PROBLEM%) do (
  for %%A in (%ALGS%) do (
    for %%S in (%SIZE%) do (
      for %%D in (%DENSITY%) do (
        echo Test: prob=%%P alg=%%A size=%%S dir=%%D
        "%EXE%" --test %%P %%A %%S %%D %REPS% %OUT%
      )
    )
  )
)

echo.
echo All tests are finished %OUT%.
pause
