# 관리자 로그인
$Username = "administrator"
$Password = ConvertTo-SecureString "eminwon2022" -AsPlainText -Force
$Credential = New-Object System.Management.Automation.PSCredential($Username, $Password)

# 결과를 저장할 파일 생성
$OutputFile = "230803_bugcheck.txt"
if (Test-Path $OutputFile) {
    Remove-Item $OutputFile
}

# 파일에서 IP 주소 추출 및 bugcheck 확인
$IPFile = "ip.txt"
$Lines = Get-Content $IPFile
foreach ($Line in $Lines) {
    # 파일 한 줄에서 IP 주소 추출
    $IP = ($Line -split '\|')[2].Trim()
    
    # IP 주소를 사용하여 해당 장비의 시스템 로그에서 bugcheck 확인
    $BugCheck = Invoke-Command -ComputerName $IP -Credential $Credential -ScriptBlock {
        Get-EventLog -LogName System -InstanceId 1001 -Newest 1 | Select-Object TimeGenerated, EntryType, Message
    }
    
    # 결과를 파일에 저장
    Add-Content -Path $OutputFile -Value ("IP: {0}" -f $IP)
    if ($BugCheck) {
        Add-Content -Path $OutputFile -Value ("Bugcheck 정보: {0}" -f $BugCheck.Message)
    } else {
        Add-Content -Path $OutputFile -Value "Bugcheck 정보를 찾을 수 없습니다."
    }
    Add-Content -Path $OutputFile -Value "-----------------------------"
}
