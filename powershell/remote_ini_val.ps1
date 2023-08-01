# ini 서버 정보 변경 powershell
# written by jwshin 220830
# psini module import
Import-Module psini
#username 
$Username = 'administrator'
#password
$Password = ''
$pass = ConvertTo-SecureString -AsPlainText $Password -Force
$Cred = New-Object System.Management.Automation.PSCredential -ArgumentList $Username,$pass
#server ip list file load
$ipTxt=Get-Content "c:\teller_ip.txt"
    foreach($Line in $ipTxt)
    {
        # $my 변수에 session 정보 저장
        $my=New-PSSession -ComputerName $Line -credential $Cred
        Invoke-Command -ScriptBlock {
            # remote computer에서 실행될 부분
            $ini=Get-IniContent c:\ntax_teller\ntax_teller.ini
            $ini["System"]["ServerIP"]="10.10.10.130"
            $ini | Out-IniFile -Force -Encoding ASCII -FilePath c:\ntax_teller\ntax_teller.ini
        } -Session $my
    } 
# session 제거    
Remove-PSSession $my



