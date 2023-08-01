#--------- +jwshin 230330 dnpsystem
#--------- disk error 확인을 위한 powershell script

$Username = 'administrator'
$Password = ''
$pass = ConvertTo-SecureString -AsPlainText $Password -Force
$Cred = New-Object System.Management.Automation.PSCredential -ArgumentList $Username,$pass
$OutputEncoding = [System.Text.Encoding]::UTF8

#------------접속할 서버 ip의 List
$ipTxt=Get-Content "firmip.txt"
$savePath = "lof_firm.txt"


$logName = "System"
$eventID = 153

#------------foreach 문으로 접속할 서버의 ip 및 문구 Looping
 "------------------------------" | out-file -FilePath $savePath -Append
foreach($Line in $ipTxt)
{
    #------- 공백제거
    $Line = $Line.trim()
    $string = $Line
    #--------- pipeline 구분자로 구분
    $splitstring = $string.split('|')
    write $splitstring
    #--------------- 3번째 필드인 ip addr를 가져옴 
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
   
    #----------- log file 저장
    $splitstring + " " + $splitstring[2] | out-file -FilePath $savePath -Append
    $result1 | out-file -FilePath $savePath -Append

	#----------------세션 접속 해제
	Remove-PSSession -Session $mysession
}