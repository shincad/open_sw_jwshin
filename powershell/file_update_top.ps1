# file update powershell
# written by jwshin 220901
# psini module import
Import-Module psini
$LogFile = "c:\PS\Log\proc_$env:computername.log"
#Log function
function WriteLog
{
    Param ([string]$LogString)
    $Stamp = (Get-Date).toString("yyyy/MM/dd HH:mm:ss")
    $LogMessage = "$Stamp $LogString"
    Add-content $LogFile -value $LogMessage
}

#username 
$Username = 'administrator'
#password
$Password = 'eminwon2020'
$pass = ConvertTo-SecureString -AsPlainText $Password -Force
$Cred = New-Object System.Management.Automation.PSCredential -ArgumentList $Username,$pass
$Source = "C:\data_drive\develop_notebook\tax_ps_test\220830_test\ntax_top.exe"

#server ip list file load
try {
    WriteLog "Try Start"
    $ipTxt=Get-Content "c:\teller_ip.txt" -ErrorAction Stop
    foreach($Line in $ipTxt)
    {
        WriteLog $Line 
        $my=New-PSSession -ComputerName $Line -credential $Cred -ErrorAction Stop
        Copy-Item   -Path $Source -Destination "c:\ntax_top\ntax_topxxx.exe" -ToSession $my -ErrorAction Stop
        Invoke-Command -ScriptBlock {
            CD "c:\ntax_top"
            DIR
            $hashSrc = Get-FileHash "c:\ntax_top\ntax_topxxx.exe" -ErrorAction Stop
            $hashDest = Get-FileHash "c:\ntax_top\ntax_top.exe" -ErrorAction Stop
            if($hashSrc.Hash -ne $hashDest.Hash)
            {
                Write-Host "diff"
                Remove-Item -Path "C:\ntax_top\ntax_Top.exe" -ErrorAction Stop
                Rename-Item -Path "c:\ntax_top\ntax_topxxx.exe" -NewName "ntax_top.exe" -ErrorAction Stop
            }   
            else 
            {
                Remove-Item -Path "C:\ntax_top\ntax_Topxxx.exe" -ErrorAction Stop
                Write-host "Same"
            }
        } -Session $my
    } 
    # session 제거    
    Remove-PSSession $my
}
catch 
{
    Write-host "`nError Message: " $_.Exception.Message
    Write-host "`nError in Line: " $_.InvocationInfo.Line
    Write-host "`nError in Line Number: "$_.InvocationInfo.ScriptLineNumber
    Write-host "`nError Item Name: "$_.Exception.ItemName
}
finally 
{
    write-host "Done"
    $error.clear()
}