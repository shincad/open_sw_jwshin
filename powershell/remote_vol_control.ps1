#username 
$Username = ''
#password
$Password = ''
$pass = ConvertTo-SecureString -AsPlainText $Password -Force
$Cred = New-Object System.Management.Automation.PSCredential -ArgumentList $Username,$pass

    
        # $my ������ session ���� ����
        $my=New-PSSession -ComputerName 10.10.10.251 -credential $Cred
        Invoke-Command -ScriptBlock {
            Invoke-Expression -Command:"start 'notepad.exe'"
        } -Session $my
    
# session ����    
Remove-PSSession $my