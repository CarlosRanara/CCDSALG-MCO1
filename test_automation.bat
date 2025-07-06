@echo off
echo ========================================================
echo    Graham's Scan Performance Testing Script
echo    CCDSALG Term 3, AY 2024-2025
echo ========================================================

:: Check executables
if not exist main1.exe (
    echo [ERROR] main1.exe not found - compile first!
    pause
    exit
)

if not exist main2.exe (
    echo [ERROR] main2.exe not found - compile first!
    pause
    exit
)

echo [SUCCESS] Both executables found

:: Create results folder
if not exist results mkdir results

echo [INFO] Starting automated testing...
echo.

:: Test 1: 2^6 = 64 points
if exist "input2^^6.txt" (
    echo === TEST 1: input2^6.txt (64 points) ===
    echo input2^^6.txt> input.tmp
    echo results\slow_2^^6.txt>> input.tmp
    main1.exe < input.tmp > results\log_2^^6_slow.txt
    
    echo input2^^6.txt> input.tmp
    echo results\fast_2^^6.txt>> input.tmp
    main2.exe < input.tmp > results\log_2^^6_fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\log_2^^6_slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\log_2^^6_fast.txt
    echo.
)

:: Test 2: 2^7 = 128 points
if exist "input2^^7.txt" (
    echo === TEST 2: input2^7.txt (128 points) ===
    echo input2^^7.txt> input.tmp
    echo results\slow_2^^7.txt>> input.tmp
    main1.exe < input.tmp > results\log_2^^7_slow.txt
    
    echo input2^^7.txt> input.tmp
    echo results\fast_2^^7.txt>> input.tmp
    main2.exe < input.tmp > results\log_2^^7_fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\log_2^^7_slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\log_2^^7_fast.txt
    echo.
)

:: Test 3: 2^8 = 256 points
if exist "input2^^8.txt" (
    echo === TEST 3: input2^8.txt (256 points) ===
    echo input2^^8.txt> input.tmp
    echo results\slow_2^^8.txt>> input.tmp
    main1.exe < input.tmp > results\log_2^^8_slow.txt
    
    echo input2^^8.txt> input.tmp
    echo results\fast_2^^8.txt>> input.tmp
    main2.exe < input.tmp > results\log_2^^8_fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\log_2^^8_slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\log_2^^8_fast.txt
    echo.
)

:: Test 4: 2^9 = 512 points
if exist "input2^^9.txt" (
    echo === TEST 4: input2^9.txt (512 points) ===
    echo input2^^9.txt> input.tmp
    echo results\slow_2^^9.txt>> input.tmp
    main1.exe < input.tmp > results\log_2^^9_slow.txt
    
    echo input2^^9.txt> input.tmp
    echo results\fast_2^^9.txt>> input.tmp
    main2.exe < input.tmp > results\log_2^^9_fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\log_2^^9_slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\log_2^^9_fast.txt
    echo.
)

:: Test 5: 2^10 = 1024 points
if exist "input2^^10.txt" (
    echo === TEST 5: input2^10.txt (1024 points) ===
    echo input2^^10.txt> input.tmp
    echo results\slow_2^^10.txt>> input.tmp
    main1.exe < input.tmp > results\log_2^^10_slow.txt
    
    echo input2^^10.txt> input.tmp
    echo results\fast_2^^10.txt>> input.tmp
    main2.exe < input.tmp > results\log_2^^10_fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\log_2^^10_slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\log_2^^10_fast.txt
    echo.
)

:: Test 6: 2^11 = 2048 points
if exist "input2^^11.txt" (
    echo === TEST 6: input2^11.txt (2048 points) ===
    echo input2^^11.txt> input.tmp
    echo results\slow_2^^11.txt>> input.tmp
    main1.exe < input.tmp > results\log_2^^11_slow.txt
    
    echo input2^^11.txt> input.tmp
    echo results\fast_2^^11.txt>> input.tmp
    main2.exe < input.tmp > results\log_2^^11_fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\log_2^^11_slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\log_2^^11_fast.txt
    echo.
)

:: Test 7: 2^12 = 4096 points
if exist "input2^^12.txt" (
    echo === TEST 7: input2^12.txt (4096 points) ===
    echo input2^^12.txt> input.tmp
    echo results\slow_2^^12.txt>> input.tmp
    main1.exe < input.tmp > results\log_2^^12_slow.txt
    
    echo input2^^12.txt> input.tmp
    echo results\fast_2^^12.txt>> input.tmp
    main2.exe < input.tmp > results\log_2^^12_fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\log_2^^12_slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\log_2^^12_fast.txt
    echo.
)

:: Test 8: 2^13 = 8192 points
if exist "input2^^13.txt" (
    echo === TEST 8: input2^13.txt (8192 points) ===
    echo input2^^13.txt> input.tmp
    echo results\slow_2^^13.txt>> input.tmp
    main1.exe < input.tmp > results\log_2^^13_slow.txt
    
    echo input2^^13.txt> input.tmp
    echo results\fast_2^^13.txt>> input.tmp
    main2.exe < input.tmp > results\log_2^^13_fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\log_2^^13_slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\log_2^^13_fast.txt
    echo.
)

:: Test 9: 2^14 = 16384 points
if exist "input2^^14.txt" (
    echo === TEST 9: input2^14.txt (16384 points) ===
    echo input2^^14.txt> input.tmp
    echo results\slow_2^^14.txt>> input.tmp
    main1.exe < input.tmp > results\log_2^^14_slow.txt
    
    echo input2^^14.txt> input.tmp
    echo results\fast_2^^14.txt>> input.tmp
    main2.exe < input.tmp > results\log_2^^14_fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\log_2^^14_slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\log_2^^14_fast.txt
    echo.
)

:: Test 10: 2^15 = 32768 points
if exist "input2^^15.txt" (
    echo === TEST 10: input2^15.txt (32768 points) ===
    echo input2^^15.txt> input.tmp
    echo results\slow_2^^15.txt>> input.tmp
    main1.exe < input.tmp > results\log_2^^15_slow.txt
    
    echo input2^^15.txt> input.tmp
    echo results\fast_2^^15.txt>> input.tmp
    main2.exe < input.tmp > results\log_2^^15_fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\log_2^^15_slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\log_2^^15_fast.txt
    echo.
)

del input.tmp 2>nul

echo ========================================================
echo ALL TESTS COMPLETED!
echo ========================================================
echo.
echo The timing data shown above is what you need for your table.
echo Log files are saved in results\ folder for reference.
echo.

start results

pause
