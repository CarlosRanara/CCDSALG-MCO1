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

:: Test 1
if exist INPUT1.TXT (
    echo === TEST 1: INPUT1.TXT ===
    echo INPUT1.TXT> input.tmp
    echo results\slow1.txt>> input.tmp
    main1.exe < input.tmp > results\log1_slow.txt
    
    echo INPUT1.TXT> input.tmp
    echo results\fast1.txt>> input.tmp
    main2.exe < input.tmp > results\log1_fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\log1_slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\log1_fast.txt
    echo.
)

:: Test 2
if exist INPUT2.TXT (
    echo === TEST 2: INPUT2.TXT ===
    echo INPUT2.TXT> input.tmp
    echo results\slow2.txt>> input.tmp
    main1.exe < input.tmp > results\log2_slow.txt
    
    echo INPUT2.TXT> input.tmp
    echo results\fast2.txt>> input.tmp
    main2.exe < input.tmp > results\log2_fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\log2_slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\log2_fast.txt
    echo.
)

:: Test 3
if exist INPUT3.TXT (
    echo === TEST 3: INPUT3.TXT ===
    echo INPUT3.TXT> input.tmp
    echo results\slow3.txt>> input.tmp
    main1.exe < input.tmp > results\log3_slow.txt
    
    echo INPUT3.TXT> input.tmp
    echo results\fast3.txt>> input.tmp
    main2.exe < input.tmp > results\log3_fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\log3_slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\log3_fast.txt
    echo.
)

:: Test 4
if exist INPUT4.TXT (
    echo === TEST 4: INPUT4.TXT ===
    echo INPUT4.TXT> input.tmp
    echo results\slow4.txt>> input.tmp
    main1.exe < input.tmp > results\log4_slow.txt
    
    echo INPUT4.TXT> input.tmp
    echo results\fast4.txt>> input.tmp
    main2.exe < input.tmp > results\log4_fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\log4_slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\log4_fast.txt
    echo.
)

:: Test 5
if exist INPUT5.TXT (
    echo === TEST 5: INPUT5.TXT ===
    echo INPUT5.TXT> input.tmp
    echo results\slow5.txt>> input.tmp
    main1.exe < input.tmp > results\log5_slow.txt
    
    echo INPUT5.TXT> input.tmp
    echo results\fast5.txt>> input.tmp
    main2.exe < input.tmp > results\log5_fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\log5_slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\log5_fast.txt
    echo.
)

:: Test 6
if exist INPUT6.TXT (
    echo === TEST 6: INPUT6.TXT ===
    echo INPUT6.TXT> input.tmp
    echo results\slow6.txt>> input.tmp
    main1.exe < input.tmp > results\log6_slow.txt
    
    echo INPUT6.TXT> input.tmp
    echo results\fast6.txt>> input.tmp
    main2.exe < input.tmp > results\log6_fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\log6_slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\log6_fast.txt
    echo.
)

:: Test 7
if exist INPUT7.TXT (
    echo === TEST 7: INPUT7.TXT ===
    echo INPUT7.TXT> input.tmp
    echo results\slow7.txt>> input.tmp
    main1.exe < input.tmp > results\log7_slow.txt
    
    echo INPUT7.TXT> input.tmp
    echo results\fast7.txt>> input.tmp
    main2.exe < input.tmp > results\log7_fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\log7_slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\log7_fast.txt
    echo.
)

:: Test 8
if exist INPUT8.TXT (
    echo === TEST 8: INPUT8.TXT ===
    echo INPUT8.TXT> input.tmp
    echo results\slow8.txt>> input.tmp
    main1.exe < input.tmp > results\log8_slow.txt
    
    echo INPUT8.TXT> input.tmp
    echo results\fast8.txt>> input.tmp
    main2.exe < input.tmp > results\log8_fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\log8_slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\log8_fast.txt
    echo.
)

:: Test 9
if exist INPUT9.TXT (
    echo === TEST 9: INPUT9.TXT ===
    echo INPUT9.TXT> input.tmp
    echo results\slow9.txt>> input.tmp
    main1.exe < input.tmp > results\log9_slow.txt
    
    echo INPUT9.TXT> input.tmp
    echo results\fast9.txt>> input.tmp
    main2.exe < input.tmp > results\log9_fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\log9_slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\log9_fast.txt
    echo.
)

:: Test 10
if exist INPUT10.TXT (
    echo === TEST 10: INPUT10.TXT ===
    echo INPUT10.TXT> input.tmp
    echo results\slow10.txt>> input.tmp
    main1.exe < input.tmp > results\log10_slow.txt
    
    echo INPUT10.TXT> input.tmp
    echo results\fast10.txt>> input.tmp
    main2.exe < input.tmp > results\log10_fast.txt
    
    echo SLOW: 
    findstr "Bubble Sort.*execution time" results\log10_slow.txt
    echo FAST:
    findstr "Merge Sort.*execution time" results\log10_fast.txt
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