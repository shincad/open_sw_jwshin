# 감시할 프로세스 이름
$processName = "ntax_serversu"

# 프로세스를 감시하는 무한 루프
while ($true) {
    # 프로세스를 찾음
    $process = Get-Process -Name $processName -ErrorAction SilentlyContinue

    # 프로세스가 존재하지 않는 경우 또는 프로세스 상태가 Stopped인 경우
    if (-Not $process -or $process.HasExited) {
        Write-Host "$processName 프로세스가 종료되었습니다. 재시작을 시도합니다."

        # 10초 대기
        Start-Sleep -Seconds 10

        # 프로세스 재실행
        Start-Process -FilePath "C:\ntax_serversu\ntax_serversu.exe" -NoNewWindow
    }
    else {
        Write-Host "$processName 프로세스가 실행 중입니다."

        # 3초 대기 후 다시 확인
        Start-Sleep -Seconds 3
    }
}
