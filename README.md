# Description
```
                           _         _                                   _     
     /\                   (_)       | |                                 | |    
    /  \     _ __   _ __   _   ___  | |_    ___     ___   _ __    __ _  | |_   
   / /\ \   | '__| | '__| | | / __| | __|  / _ \   / __| | '__|  / _` | | __|  
  / ____ \  | |    | |    | | \__ \ | |_  | (_) | | (__  | |    | (_| | | |_   
 /_/    \_\ |_|    |_|    |_| |___/  \__|  \___/   \___| |_|     \__,_|  \__|  
                                                                               
 andrew.borg@minerva.com.mt                                       by Minerva IS
                                                                            
Password of the Day (POTD) generator for Arris Cable Modems
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Functions: 
	Generate a Password of the Day using the -P switch.
	Decrypt an Arris CM seed using the -D switch.
	Encrypt a cleartext seed for use with Arris CMs using the -E switch.
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Usage:
	 ./Arristocrat -P [Custom Seed]
	 ./Arristocrat -D <Arris Encrypted Seed>	
	 ./Arristocrat -E <Cleartext Seed>	
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Examples:
	 Generate POTD using the default Seed:
		  ./Arristocrat -P 
	 Generate POTD using a custom Seed:
		 ./Arristocrat -P MySeed 
	 Encrypt a seed value for use with Arris CMs:
		 ./Arristocrat -E Enc1Seed 
	 Decrypt a seed value being used on Arris CMs:
		 ./Arristocrat -D 0xF4BC50A0C5FC3B93 

```

# Building

`make`
