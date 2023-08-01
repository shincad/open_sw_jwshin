# ini 서버 정보 변경 powershell
# written by jwshin 220830
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
$Password = 'eminwon2022'
$pass = ConvertTo-SecureString -AsPlainText $Password -Force
$Cred = New-Object System.Management.Automation.PSCredential -ArgumentList $Username,$pass
#server ip list file load
try {

    $ipTxt=Get-Content "c:\teller_ip.txt" -ErrorAction Stop
        foreach($Line in $ipTxt)
        {
            # $my 변수에 session 정보 저장
            $my=New-PSSession -ComputerName $Line -credential $Cred -ErrorAction Stop
            Invoke-Command -ScriptBlock {
                # remote computer에서 실행될 부분
                $ini=Get-IniContent c:\ntax_gate\ntax_gate.ini
                if($ini["System"]["ServerIP"])
                {
                    $ini["System"]["ServerIP"]="10.10.10.180"
                    $ini | Out-IniFile -Force -Encoding ASCII -FilePath c:\ntax_gate\ntax_gate.ini
                }              
                else 
                {
                    Write-host "ini[System][ServerIP]= is not found"    
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