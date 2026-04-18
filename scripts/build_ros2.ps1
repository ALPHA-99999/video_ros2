param(
    [string]$Workspace = $PSScriptRoot + '\..'
)

$ErrorActionPreference = 'Stop'
Push-Location (Resolve-Path $Workspace)
try {
    colcon build --merge-install --cmake-args -DCMAKE_BUILD_TYPE=Release
}
finally {
    Pop-Location
}