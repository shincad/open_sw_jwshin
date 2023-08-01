try {
   New-Item -Path C:\doesnotexist -Name myfile.txt -ItemType File -ErrorAction Stop
}
catch {
   Write-warning $Error[0]
}