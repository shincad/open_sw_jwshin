# ������ ���μ��� �̸�
$processName = "ntax_serversu"

# ���μ����� �����ϴ� ���� ����
while ($true) {
    # ���μ����� ã��
    $process = Get-Process -Name $processName -ErrorAction SilentlyContinue

    # ���μ����� �������� �ʴ� ��� �Ǵ� ���μ��� ���°� Stopped�� ���
    if (-Not $process -or $process.HasExited) {
        Write-Host "$processName ���μ����� ����Ǿ����ϴ�. ������� �õ��մϴ�."

        # 10�� ���
        Start-Sleep -Seconds 10

        # ���μ��� �����
        Start-Process -FilePath "C:\ntax_serversu\ntax_serversu.exe" -NoNewWindow
    }
    else {
        Write-Host "$processName ���μ����� ���� ���Դϴ�."

        # 3�� ��� �� �ٽ� Ȯ��
        Start-Sleep -Seconds 3
    }
}
