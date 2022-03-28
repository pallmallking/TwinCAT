=================================================================================================================================================

Installation	

------------------------------------------------------------------------------------------------------------------------------------------------

	1. Libraries

		The following assemblies have to be installed to the "Global Assembly Cache":

			"\Ads Api\TcAdsWcf\PollingDuplex\v3.0\System.ServiceModel.PollingDuplex.dll"
			"\Ads Api\TcAdsWcf\PollingDuplex\v4.0\System.ServiceModel.PollingDuplex.dll"


------------------------------------------------------------------------------------------------------------------------------------------------

	2. Install "TcAdsWcfHost.exe" as Windows Service

		Step 1:
		
			Open the command prompt as Administrator and use the InstallUtil.exe (part of the .NET Framework) to create the Windows service.

		Step 2:

			Switch to "Control Panel\Administrative Tools\Services" and start the "TcAdsWcfHost" Service.

------------------------------------------------------------------------------------------------------------------------------------------------

	3. Test if Service is running.

			Open a browser and go to "http://localhost:8003/TwinCAT/Ads/Wcf/TcAdsService" to test the service.

------------------------------------------------------------------------------------------------------------------------------------------------
=================================================================================================================================================

Logging

------------------------------------------------------------------------------------------------------------------------------------------------
	
	Enable logging:
  
		1.	Open "TcAdsWcfHost.exe.config" in TcAdsWcf directory.

		2.	Navigate to the "userSettings/TwinCAT.Ads.Wcf.Properties.Settings" node.

			<userSettings>
				<TwinCAT.Ads.Wcf.Properties.Settings>
					<setting name="LogLevel" serializeAs="String">
						<value>NONE</value>
					</setting>
					<setting name="LogFilePath" serializeAs="String">
						<value>C:\TcAdsWcf_Log.txt</value>
					</setting>
				</TwinCAT.Ads.Wcf.Properties.Settings>
			</userSettings>

		3. Set the value of the "LogLevel" setting to "INFO" or "ERROR"

		4. Define the path to the logfile as vaue of the "LogFilePath" setting.

------------------------------------------------------------------------------------------------------------------------------------------------

	LogLevel Description:
		
		NONE:	Nothing is logged.

		INFO:	Information about method calls with parameter values and errors are logged.

		ERROR:	Erros are logged.
