#username 
$Username = ''
#password
$Password = ''
$pass = ConvertTo-SecureString -AsPlainText $Password -Force
$Cred = New-Object System.Management.Automation.PSCredential -ArgumentList $Username,$pass

    
        # $my 변수에 session 정보 저장
        $my=New-PSSession -ComputerName 10.10.10.251 -credential $Cred
        Invoke-Command -ScriptBlock {
            Invoke-Expression -Command:"start 'notepad.exe'"
        } -Session $my
    
# session 제거    
Remove-PSSession $my