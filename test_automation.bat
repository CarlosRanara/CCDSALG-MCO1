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
if exist "data\input2^^6.txt" (
    echo === TEST 1: input2^6.txt (64 points) ===
    echo data\input2^^6.txt> input.tmp
    echo results\OUTPUT1-slow.txt>> input.tmp
    main1.exe < input.tmp > results\OUTPUT-log1-slow.txt
    
    echo data\input2^^6.txt> input.tmp
    echo results\OUTPUT1-fast.txt>> input.tmp
    main2.exe < input.tmp > results\OUTPUT-log1-fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\OUTPUT-log1-slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\OUTPUT-log1-fast.txt
    echo.
)

:: Test 2: 2^7 = 128 points
if exist "data\input2^^7.txt" (
    echo === TEST 2: input2^7.txt (128 points) ===
    echo data\input2^^7.txt> input.tmp
    echo results\OUTPUT2-slow.txt>> input.tmp
    main1.exe < input.tmp > results\OUTPUT-log2-slow.txt
    
    echo data\input2^^7.txt> input.tmp
    echo results\OUTPUT2-fast.txt>> input.tmp
    main2.exe < input.tmp > results\OUTPUT-log2-fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\OUTPUT-log2-slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\OUTPUT-log2-fast.txt
    echo.
)

:: Test 3: 2^8 = 256 points
if exist "data\input2^^8.txt" (
    echo === TEST 3: input2^8.txt (256 points) ===
    echo data\input2^^8.txt> input.tmp
    echo results\OUTPUT3-slow.txt>> input.tmp
    main1.exe < input.tmp > results\OUTPUT-log3-slow.txt
    
    echo data\input2^^8.txt> input.tmp
    echo results\OUTPUT3-fast.txt>> input.tmp
    main2.exe < input.tmp > results\OUTPUT-log3-fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\OUTPUT-log3-slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\OUTPUT-log3-fast.txt
    echo.
)

:: Test 4: 2^9 = 512 points
if exist "data\input2^^9.txt" (
    echo === TEST 4: input2^9.txt (512 points) ===
    echo data\input2^^9.txt> input.tmp
    echo results\OUTPUT4-slow.txt>> input.tmp
    main1.exe < input.tmp > results\OUTPUT-log4-slow.txt
    
    echo data\input2^^9.txt> input.tmp
    echo results\OUTPUT4-fast.txt>> input.tmp
    main2.exe < input.tmp > results\OUTPUT-log4-fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\OUTPUT-log4-slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\OUTPUT-log4-fast.txt
    echo.
)

:: Test 5: 2^10 = 1024 points
if exist "data\input2^^10.txt" (
    echo === TEST 5: input2^10.txt (1024 points) ===
    echo data\input2^^10.txt> input.tmp
    echo results\OUTPUT5-slow.txt>> input.tmp
    main1.exe < input.tmp > results\OUTPUT-log5-slow.txt
    
    echo data\input2^^10.txt> input.tmp
    echo results\OUTPUT5-fast.txt>> input.tmp
    main2.exe < input.tmp > results\OUTPUT-log5-fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\OUTPUT-log5-slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\OUTPUT-log5-fast.txt
    echo.
)

:: Test 6: 2^11 = 2048 points
if exist "data\input2^^11.txt" (
    echo === TEST 6: input2^11.txt (2048 points) ===
    echo data\input2^^11.txt> input.tmp
    echo results\OUTPUT6-slow.txt>> input.tmp
    main1.exe < input.tmp > results\OUTPUT-log6-slow.txt
    
    echo data\input2^^11.txt> input.tmp
    echo results\OUTPUT6-fast.txt>> input.tmp
    main2.exe < input.tmp > results\OUTPUT-log6-fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\OUTPUT-log6-slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\OUTPUT-log6-fast.txt
    echo.
)

:: Test 7: 2^12 = 4096 points
if exist "data\input2^^12.txt" (
    echo === TEST 7: input2^12.txt (4096 points) ===
    echo data\input2^^12.txt> input.tmp
    echo results\OUTPUT7-slow.txt>> input.tmp
    main1.exe < input.tmp > results\OUTPUT-log7-slow.txt
    
    echo data\input2^^12.txt> input.tmp
    echo results\OUTPUT7-fast.txt>> input.tmp
    main2.exe < input.tmp > results\OUTPUT-log7-fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\OUTPUT-log7-slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\OUTPUT-log7-fast.txt
    echo.
)

:: Test 8: 2^13 = 8192 points
if exist "data\input2^^13.txt" (
    echo === TEST 8: input2^13.txt (8192 points) ===
    echo data\input2^^13.txt> input.tmp
    echo results\OUTPUT8-slow.txt>> input.tmp
    main1.exe < input.tmp > results\OUTPUT-log8-slow.txt
    
    echo data\input2^^13.txt> input.tmp
    echo results\OUTPUT8-fast.txt>> input.tmp
    main2.exe < input.tmp > results\OUTPUT-log8-fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\OUTPUT-log8-slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\OUTPUT-log8-fast.txt
    echo.
)

:: Test 9: 2^14 = 16384 points
if exist "data\input2^^14.txt" (
    echo === TEST 9: input2^14.txt (16384 points) ===
    echo data\input2^^14.txt> input.tmp
    echo results\OUTPUT9-slow.txt>> input.tmp
    main1.exe < input.tmp > results\OUTPUT-log9-slow.txt
    
    echo data\input2^^14.txt> input.tmp
    echo results\OUTPUT9-fast.txt>> input.tmp
    main2.exe < input.tmp > results\OUTPUT-log9-fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\OUTPUT-log9-slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\OUTPUT-log9-fast.txt
    echo.
)

:: Test 10: 2^15 = 32768 points
if exist "data\input2^^15.txt" (
    echo === TEST 10: input2^15.txt (32768 points) ===
    echo data\input2^^15.txt> input.tmp
    echo results\OUTPUT10-slow.txt>> input.tmp
    main1.exe < input.tmp > results\OUTPUT-log10-slow.txt
    
    echo data\input2^^15.txt> input.tmp
    echo results\OUTPUT10-fast.txt>> input.tmp
    main2.exe < input.tmp > results\OUTPUT-log10-fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\OUTPUT-log10-slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\OUTPUT-log10-fast.txt
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
