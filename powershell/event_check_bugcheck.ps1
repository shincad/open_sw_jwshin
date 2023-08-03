# ������ �α���
$Username = "administrator"
$Password = ConvertTo-SecureString "eminwon2022" -AsPlainText -Force
$Credential = New-Object System.Management.Automation.PSCredential($Username, $Password)

# ����� ������ ���� ����
$OutputFile = "230803_bugcheck.txt"
if (Test-Path $OutputFile) {
    Remove-Item $OutputFile
}

# ���Ͽ��� IP �ּ� ���� �� bugcheck Ȯ��
$IPFile = "ip.txt"
$Lines = Get-Content $IPFile
foreach ($Line in $Lines) {
    # ���� �� �ٿ��� IP �ּ� ����
    $IP = ($Line -split '\|')[2].Trim()
    
    # IP �ּҸ� ����Ͽ� �ش� ����� �ý��� �α׿��� bugcheck Ȯ��
    $BugCheck = Invoke-Command -ComputerName $IP -Credential $Credential -ScriptBlock {
        Get-EventLog -LogName System -InstanceId 1001 -Newest 1 | Select-Object TimeGenerated, EntryType, Message
    }
    
    # ����� ���Ͽ� ����
    Add-Content -Path $OutputFile -Value ("IP: {0}" -f $IP)
    if ($BugCheck) {
        Add-Content -Path $OutputFile -Value ("Bugcheck ����: {0}" -f $BugCheck.Message)
    } else {
        Add-Content -Path $OutputFile -Value "Bugcheck ������ ã�� �� �����ϴ�."
    }
    Add-Content -Path $OutputFile -Value "-----------------------------"
}
