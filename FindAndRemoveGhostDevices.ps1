# Goal of this scripts is:
# 1. show all "Ghost" devices
# 2. for those that are wished to be removed - remove them

# Show all ghost devices
Get-PnpDevice -status UNKNOWN

#  Get the desirt device name from above 

$string_to_remove = "*SOME EXPLICIT NAME OF A DEVICE TO REMOVE FROM THE PNP LIST AND DRIVER MANAGER *"
$dev = (Get-PnpDevice | Where-Object { $_.Name -like $string_to_remove })
foreach ($d in $dev) {
	echo "removing $d.InstanceId"
	$s1 = $d.InstanceId
	$s = "`"@$s1`"" 
	 .\devcon.exe remove $s
 }
