
if (Test-Path build) { 
    Remove-Item -Recurse -Force build 
}

New-Item -ItemType Directory -Force -Path build | Out-Null

Set-Location build

cmake .. -G "Visual Studio 17 2022" -A x64

cmake --build . --config Release

Set-Location ..

Write-Host "`nBuild complete! Executable: build\Release\opencv_test.exe" -ForegroundColor Green
