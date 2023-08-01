#--------- +jwshin 230330 dnpsystem
#--------- disk error Ȯ���� ���� powershell script

$Username = 'administrator'
$Password = ''
$pass = ConvertTo-SecureString -AsPlainText $Password -Force
$Cred = New-Object System.Management.Automation.PSCredential -ArgumentList $Username,$pass
$OutputEncoding = [System.Text.Encoding]::UTF8

#------------������ ���� ip�� List
$ipTxt=Get-Content "firmip.txt"
$savePath = "lof_firm.txt"


$logName = "System"
$eventID = 153

#------------foreach ������ ������ ������ ip �� ���� Looping
 "------------------------------" | out-file -FilePath $savePath -Append
foreach($Line in $ipTxt)
{
    #------- ��������
    $Line = $Line.trim()
    $string = $Line
    #--------- pipeline �����ڷ� ����
    $splitstring = $string.split('|')
    write $splitstring
    #--------------- 3��° �ʵ��� ip addr�� ������ 
	$mysession=New-PSSession -ComputerName $splitstring[2] -credential $Cred
    $result1 = @()
    $result1 = Invoke-Command -ScriptBlock {
        try
        {
            Get-PhysicalDisk | Get-StorageFirmwareInformation
            #----------- disk error 
	        Get-EventLog -LogName system -Source Disk 
            
        }
        catch
        {
            	$errormessage = $_.Exception.Message
			    Write-Host "$errorMessage"
        }

	} -Session $mysession 
   
    #----------- log file ����
    $splitstring + " " + $splitstring[2] | out-file -FilePath $savePath -Append
    $result1 | out-file -FilePath $savePath -Append

	#----------------���� ���� ����
	Remove-PSSession -Session $mysession
}