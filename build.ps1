# Custom build script (windows powershell).
#
# Usage:
#    .\build.ps1: clean, compile and run
#    .\build.ps1 -clean: clean compiled file
#    .\build.ps1 -cleanAndCompile: clean compiled file and compile the project
#    .\build.ps1 -compile: compile the project
#    .\build.ps1 -compileAndRun: compile the project and run the compiled file
#    .\build.ps1 -run: run the compiled file
#
# Author: Prof. Dr. David Buzatto

param(
    [switch]$clean,
    [switch]$cleanAndCompile,
    [switch]$compile,
    [switch]$compileAndRun,
    [switch]$run
);

$CurrentFolderName = Split-Path -Path (Get-Location) -Leaf
$CompiledFile = "$CurrentFolderName.exe"

$all = $false
if ( -not( $clean -or $cleanAndCompile -or $compile -or $compileAndRun -or $run ) ) {
    $all = $true
}

# clean
if ( $clean -or $cleanAndCompile -or $all ) {
    Write-Host "Cleaning..."
    if ( Test-Path $CompiledFile ) {
        Remove-Item $CompiledFile
    }
}

# compile
if ( $compile -or $cleanAndCompile -or $compileAndRun -or $all ) {
    Write-Host "Compiling..."
    g++ src/*.cpp -o $CompiledFile `
        -O1 `
        -Wall `
        -Wextra `
        -Wno-unused-parameter `
        -pedantic-errors `
        -std=c++20 `
        -Wno-missing-braces `
        -I src/include/ `
        -I src/include/external `
        -L lib/ `
        -lraylib `
        -lopengl32 `
        -lgdi32 `
        -lwinmm
}

# run
if ( $run -or $compileAndRun -or $all ) {
    Write-Host "Running..."
    if ( Test-Path $CompiledFile ) {
        & .\$CompiledFile
    } else {
        Write-Host "$CompiledFile does not exists!"
    }
}