<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="13008000">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="IOScan.Faults" Type="Str"></Property>
		<Property Name="IOScan.NetVarPeriod" Type="UInt">100</Property>
		<Property Name="IOScan.NetWatchdogEnabled" Type="Bool">false</Property>
		<Property Name="IOScan.Period" Type="UInt">10000</Property>
		<Property Name="IOScan.PowerupMode" Type="UInt">0</Property>
		<Property Name="IOScan.Priority" Type="UInt">9</Property>
		<Property Name="IOScan.ReportModeConflict" Type="Bool">true</Property>
		<Property Name="IOScan.StartEngineOnDeploy" Type="Bool">false</Property>
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Dependencies" Type="Dependencies"/>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
	<Item Name="myRIO" Type="RT myRIO">
		<Property Name="alias.name" Type="Str">myRIO</Property>
		<Property Name="alias.value" Type="Str">172.22.11.2</Property>
		<Property Name="CCSymbols" Type="Str">OS,Linux;CPU,ARM;DeviceCode,76D3;TARGET_TYPE,RT;</Property>
		<Property Name="crio.ControllerPID" Type="Str">76D3</Property>
		<Property Name="crio.family" Type="Str">ARMLinux</Property>
		<Property Name="host.ResponsivenessCheckEnabled" Type="Bool">true</Property>
		<Property Name="host.ResponsivenessCheckPingDelay" Type="UInt">5000</Property>
		<Property Name="host.ResponsivenessCheckPingTimeout" Type="UInt">1000</Property>
		<Property Name="host.TargetCPUID" Type="UInt">8</Property>
		<Property Name="host.TargetOSID" Type="UInt">8</Property>
		<Property Name="target.cleanupVisa" Type="Bool">false</Property>
		<Property Name="target.FPProtocolGlobals_ControlTimeLimit" Type="Int">300</Property>
		<Property Name="target.getDefault-&gt;WebServer.Port" Type="Int">80</Property>
		<Property Name="target.getDefault-&gt;WebServer.Timeout" Type="Int">60</Property>
		<Property Name="target.IOScan.Faults" Type="Str"></Property>
		<Property Name="target.IOScan.NetVarPeriod" Type="UInt">100</Property>
		<Property Name="target.IOScan.NetWatchdogEnabled" Type="Bool">false</Property>
		<Property Name="target.IOScan.Period" Type="UInt">10000</Property>
		<Property Name="target.IOScan.PowerupMode" Type="UInt">0</Property>
		<Property Name="target.IOScan.Priority" Type="UInt">0</Property>
		<Property Name="target.IOScan.ReportModeConflict" Type="Bool">true</Property>
		<Property Name="target.IsRemotePanelSupported" Type="Bool">true</Property>
		<Property Name="target.RTCPULoadMonitoringEnabled" Type="Bool">true</Property>
		<Property Name="target.RTDebugWebServerHTTPPort" Type="Int">8001</Property>
		<Property Name="target.RTTarget.ApplicationPath" Type="Path">/c/ni-rt/startup/startup.rtexe</Property>
		<Property Name="target.RTTarget.EnableFileSharing" Type="Bool">true</Property>
		<Property Name="target.RTTarget.IPAccess" Type="Str">+*</Property>
		<Property Name="target.RTTarget.LaunchAppAtBoot" Type="Bool">false</Property>
		<Property Name="target.RTTarget.VIPath" Type="Path">/c/ni-rt/startup</Property>
		<Property Name="target.server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="target.server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="target.server.tcp.access" Type="Str">+*</Property>
		<Property Name="target.server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="target.server.tcp.paranoid" Type="Bool">true</Property>
		<Property Name="target.server.tcp.port" Type="Int">3363</Property>
		<Property Name="target.server.tcp.serviceName" Type="Str">Main Application Instance/VI Server</Property>
		<Property Name="target.server.tcp.serviceName.default" Type="Str">Main Application Instance/VI Server</Property>
		<Property Name="target.server.vi.access" Type="Str">+*</Property>
		<Property Name="target.server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="target.server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="target.WebServer.Config" Type="Str">Listen 8000

NI.ServerName default
DocumentRoot "$LVSERVER_DOCROOT"
TypesConfig "$LVSERVER_CONFIGROOT/mime.types"
DirectoryIndex index.htm
WorkerLimit 10
InactivityTimeout 60

LoadModulePath "$LVSERVER_MODULEPATHS"
LoadModule LVAuth lvauthmodule
LoadModule LVRFP lvrfpmodule

#
# Pipeline Definition
#

SetConnector netConnector

AddHandler LVAuth
AddHandler LVRFP

AddHandler fileHandler ""

AddOutputFilter chunkFilter


</Property>
		<Property Name="target.WebServer.Enabled" Type="Bool">false</Property>
		<Property Name="target.WebServer.LogEnabled" Type="Bool">false</Property>
		<Property Name="target.WebServer.LogPath" Type="Path">/c/ni-rt/system/www/www.log</Property>
		<Property Name="target.WebServer.Port" Type="Int">80</Property>
		<Property Name="target.WebServer.RootPath" Type="Path">/c/ni-rt/system/www</Property>
		<Property Name="target.WebServer.TcpAccess" Type="Str">c+*</Property>
		<Property Name="target.WebServer.Timeout" Type="Int">60</Property>
		<Property Name="target.WebServer.ViAccess" Type="Str">+*</Property>
		<Property Name="target.webservices.SecurityAPIKey" Type="Str">PqVr/ifkAQh+lVrdPIykXlFvg12GhhQFR8H9cUhphgg=:pTe9HRlQuMfJxAG6QCGq7UvoUpJzAzWGKy5SbZ+roSU=</Property>
		<Property Name="target.webservices.ValidTimestampWindow" Type="Int">15</Property>
		<Item Name="Actuator" Type="Folder">
			<Item Name="Digital Outputs.vi" Type="VI" URL="../Actuator/Digital Outputs.vi"/>
			<Item Name="Drive Direct.vi" Type="VI" URL="../Actuator/Drive Direct.vi"/>
			<Item Name="Drive Direction.ctl" Type="VI" URL="../Actuator/Drive Direction.ctl"/>
			<Item Name="Drive Direction.vi" Type="VI" URL="../Actuator/Drive Direction.vi"/>
			<Item Name="Drive Radius.vi" Type="VI" URL="../Actuator/Drive Radius.vi"/>
			<Item Name="LED.ctl" Type="VI" URL="../Actuator/LED.ctl"/>
			<Item Name="LED.vi" Type="VI" URL="../Actuator/LED.vi"/>
			<Item Name="PWM Low-Side Driver.vi" Type="VI" URL="../Actuator/PWM Low-Side Driver.vi"/>
			<Item Name="Song Define.vi" Type="VI" URL="../Actuator/Song Define.vi"/>
			<Item Name="Song Note.ctl" Type="VI" URL="../Actuator/Song Note.ctl"/>
			<Item Name="Song Play.vi" Type="VI" URL="../Actuator/Song Play.vi"/>
			<Item Name="Stop.vi" Type="VI" URL="../Actuator/Stop.vi"/>
		</Item>
		<Item Name="Advanced" Type="Folder">
			<Item Name="Command" Type="Folder">
				<Item Name="Baud.ctl" Type="VI" URL="../Advanced/Command/Baud.ctl"/>
				<Item Name="Baud.vi" Type="VI" URL="../Advanced/Command/Baud.vi"/>
				<Item Name="Demo Numbers.ctl" Type="VI" URL="../Advanced/Command/Demo Numbers.ctl"/>
				<Item Name="Demo Stop.vi" Type="VI" URL="../Advanced/Command/Demo Stop.vi"/>
				<Item Name="Demo.vi" Type="VI" URL="../Advanced/Command/Demo.vi"/>
				<Item Name="Full.vi" Type="VI" URL="../Advanced/Command/Full.vi"/>
				<Item Name="OpCode.ctl" Type="VI" URL="../Advanced/Command/OpCode.ctl"/>
				<Item Name="Safe.vi" Type="VI" URL="../Advanced/Command/Safe.vi"/>
				<Item Name="Start.vi" Type="VI" URL="../Advanced/Command/Start.vi"/>
			</Item>
			<Item Name="UART" Type="Folder">
				<Item Name="iRobot UART Byte Array Checksum.vi" Type="VI" URL="../Advanced/UART/iRobot UART Byte Array Checksum.vi"/>
				<Item Name="iRobot UART Bytes at Port.vi" Type="VI" URL="../Advanced/UART/iRobot UART Bytes at Port.vi"/>
				<Item Name="iRobot UART Close.vi" Type="VI" URL="../Advanced/UART/iRobot UART Close.vi"/>
				<Item Name="iRobot UART Open.vi" Type="VI" URL="../Advanced/UART/iRobot UART Open.vi"/>
				<Item Name="iRobot UART Port Type.ctl" Type="VI" URL="../Advanced/UART/iRobot UART Port Type.ctl"/>
				<Item Name="iRobot UART Read Flush.vi" Type="VI" URL="../Advanced/UART/iRobot UART Read Flush.vi"/>
				<Item Name="iRobot UART Read Simple Packet.vi" Type="VI" URL="../Advanced/UART/iRobot UART Read Simple Packet.vi"/>
				<Item Name="iRobot UART Read.vi" Type="VI" URL="../Advanced/UART/iRobot UART Read.vi"/>
				<Item Name="iRobot UART Simple Packet Configuration.ctl" Type="VI" URL="../Advanced/UART/iRobot UART Simple Packet Configuration.ctl"/>
				<Item Name="iRobot UART Write.vi" Type="VI" URL="../Advanced/UART/iRobot UART Write.vi"/>
			</Item>
		</Item>
		<Item Name="Examples" Type="Folder">
			<Item Name="iRobot Example - Poll Sensor.vi" Type="VI" URL="../Examples/iRobot Example - Poll Sensor.vi"/>
			<Item Name="iRobot Example - Sensor Stream.vi" Type="VI" URL="../Examples/iRobot Example - Sensor Stream.vi"/>
			<Item Name="iRobot Example - Square.vi" Type="VI" URL="../Examples/iRobot Example - Square.vi"/>
		</Item>
		<Item Name="Sensor" Type="Folder">
			<Item Name="Advanced" Type="Folder">
				<Item Name="Parse 8.vi" Type="VI" URL="../Sensor/Advanced/Parse 8.vi"/>
				<Item Name="Parse 16.vi" Type="VI" URL="../Sensor/Advanced/Parse 16.vi"/>
				<Item Name="Parse Boolean.vi" Type="VI" URL="../Sensor/Advanced/Parse Boolean.vi"/>
				<Item Name="Parse Bumps + Wheel Drops.vi" Type="VI" URL="../Sensor/Advanced/Parse Bumps + Wheel Drops.vi"/>
				<Item Name="Parse Buttons.vi" Type="VI" URL="../Sensor/Advanced/Parse Buttons.vi"/>
				<Item Name="Parse Cargo Bay Digital Inputs.vi" Type="VI" URL="../Sensor/Advanced/Parse Cargo Bay Digital Inputs.vi"/>
				<Item Name="Parse Charging Sources Available.vi" Type="VI" URL="../Sensor/Advanced/Parse Charging Sources Available.vi"/>
				<Item Name="Parse Low-Side Driver + Wheel Overcurrents.vi" Type="VI" URL="../Sensor/Advanced/Parse Low-Side Driver + Wheel Overcurrents.vi"/>
				<Item Name="Parse Sensor Group 0.vi" Type="VI" URL="../Sensor/Advanced/Parse Sensor Group 0.vi"/>
				<Item Name="Parse Sensor Group 1.vi" Type="VI" URL="../Sensor/Advanced/Parse Sensor Group 1.vi"/>
				<Item Name="Parse Sensor Group 2.vi" Type="VI" URL="../Sensor/Advanced/Parse Sensor Group 2.vi"/>
				<Item Name="Parse Sensor Group 3.vi" Type="VI" URL="../Sensor/Advanced/Parse Sensor Group 3.vi"/>
				<Item Name="Parse Sensor Group 4.vi" Type="VI" URL="../Sensor/Advanced/Parse Sensor Group 4.vi"/>
				<Item Name="Parse Sensor Group 5.vi" Type="VI" URL="../Sensor/Advanced/Parse Sensor Group 5.vi"/>
				<Item Name="Parse Sensor Group 6.vi" Type="VI" URL="../Sensor/Advanced/Parse Sensor Group 6.vi"/>
			</Item>
			<Item Name="Polling" Type="Folder">
				<Item Name="Poll All Sensors.vi" Type="VI" URL="../Sensor/Polling/Poll All Sensors.vi"/>
				<Item Name="Poll Sensor Group 0.vi" Type="VI" URL="../Sensor/Polling/Poll Sensor Group 0.vi"/>
				<Item Name="Poll Sensor Group 1.vi" Type="VI" URL="../Sensor/Polling/Poll Sensor Group 1.vi"/>
				<Item Name="Poll Sensor Group 2.vi" Type="VI" URL="../Sensor/Polling/Poll Sensor Group 2.vi"/>
				<Item Name="Poll Sensor Group 3.vi" Type="VI" URL="../Sensor/Polling/Poll Sensor Group 3.vi"/>
				<Item Name="Poll Sensor Group 4.vi" Type="VI" URL="../Sensor/Polling/Poll Sensor Group 4.vi"/>
				<Item Name="Poll Sensor Group 5.vi" Type="VI" URL="../Sensor/Polling/Poll Sensor Group 5.vi"/>
				<Item Name="Poll Sensor Group 6.vi" Type="VI" URL="../Sensor/Polling/Poll Sensor Group 6.vi"/>
				<Item Name="Poll Sensor.vi" Type="VI" URL="../Sensor/Polling/Poll Sensor.vi"/>
			</Item>
			<Item Name="Streaming" Type="Folder">
				<Item Name="Stream Begin All Sensors.vi" Type="VI" URL="../Sensor/Streaming/Stream Begin All Sensors.vi"/>
				<Item Name="Stream Configure.vi" Type="VI" URL="../Sensor/Streaming/Stream Configure.vi"/>
				<Item Name="Stream Pause.vi" Type="VI" URL="../Sensor/Streaming/Stream Pause.vi"/>
				<Item Name="Stream Update All Sensors.vi" Type="VI" URL="../Sensor/Streaming/Stream Update All Sensors.vi"/>
			</Item>
			<Item Name="Bumps + Wheel Drops.ctl" Type="VI" URL="../Sensor/Bumps + Wheel Drops.ctl"/>
			<Item Name="Buttons.ctl" Type="VI" URL="../Sensor/Buttons.ctl"/>
			<Item Name="Cargo Bay Digital Inputs.ctl" Type="VI" URL="../Sensor/Cargo Bay Digital Inputs.ctl"/>
			<Item Name="Charging Sources Available.ctl" Type="VI" URL="../Sensor/Charging Sources Available.ctl"/>
			<Item Name="Charging State.ctl" Type="VI" URL="../Sensor/Charging State.ctl"/>
			<Item Name="Low-Side Driver + Wheel Overcurrent.ctl" Type="VI" URL="../Sensor/Low-Side Driver + Wheel Overcurrent.ctl"/>
			<Item Name="OI Mode.ctl" Type="VI" URL="../Sensor/OI Mode.ctl"/>
			<Item Name="Sensor Group 0.ctl" Type="VI" URL="../Sensor/Sensor Group 0.ctl"/>
			<Item Name="Sensor Group 1.ctl" Type="VI" URL="../Sensor/Sensor Group 1.ctl"/>
			<Item Name="Sensor Group 2.ctl" Type="VI" URL="../Sensor/Sensor Group 2.ctl"/>
			<Item Name="Sensor Group 3.ctl" Type="VI" URL="../Sensor/Sensor Group 3.ctl"/>
			<Item Name="Sensor Group 4.ctl" Type="VI" URL="../Sensor/Sensor Group 4.ctl"/>
			<Item Name="Sensor Group 5.ctl" Type="VI" URL="../Sensor/Sensor Group 5.ctl"/>
			<Item Name="Sensor Group 6.ctl" Type="VI" URL="../Sensor/Sensor Group 6.ctl"/>
			<Item Name="Sensor ID.ctl" Type="VI" URL="../Sensor/Sensor ID.ctl"/>
		</Item>
		<Item Name="iRobot Close.vi" Type="VI" URL="../iRobot Close.vi"/>
		<Item Name="iRobot Create Readme.pdf" Type="Document" URL="../iRobot Create Readme.pdf"/>
		<Item Name="iRobot Open.vi" Type="VI" URL="../iRobot Open.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="BuildHelpPath.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/BuildHelpPath.vi"/>
				<Item Name="Check Special Tags.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Check Special Tags.vi"/>
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="Convert property node font to graphics font.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Convert property node font to graphics font.vi"/>
				<Item Name="Details Display Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Details Display Dialog.vi"/>
				<Item Name="DialogType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogType.ctl"/>
				<Item Name="DialogTypeEnum.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogTypeEnum.ctl"/>
				<Item Name="Error Code Database.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Code Database.vi"/>
				<Item Name="ErrWarn.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/ErrWarn.ctl"/>
				<Item Name="eventvkey.ctl" Type="VI" URL="/&lt;vilib&gt;/event_ctls.llb/eventvkey.ctl"/>
				<Item Name="Find Tag.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Find Tag.vi"/>
				<Item Name="Format Message String.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Format Message String.vi"/>
				<Item Name="General Error Handler CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler CORE.vi"/>
				<Item Name="General Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler.vi"/>
				<Item Name="Get String Text Bounds.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Get String Text Bounds.vi"/>
				<Item Name="Get Text Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Get Text Rect.vi"/>
				<Item Name="GetHelpDir.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetHelpDir.vi"/>
				<Item Name="GetRTHostConnectedProp.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetRTHostConnectedProp.vi"/>
				<Item Name="Longest Line Length in Pixels.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Longest Line Length in Pixels.vi"/>
				<Item Name="LVBoundsTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVBoundsTypeDef.ctl"/>
				<Item Name="Not Found Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Not Found Dialog.vi"/>
				<Item Name="Search and Replace Pattern.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Search and Replace Pattern.vi"/>
				<Item Name="Set Bold Text.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set Bold Text.vi"/>
				<Item Name="Set String Value.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set String Value.vi"/>
				<Item Name="Simple Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Simple Error Handler.vi"/>
				<Item Name="TagReturnType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/TagReturnType.ctl"/>
				<Item Name="Three Button Dialog CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog CORE.vi"/>
				<Item Name="Three Button Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog.vi"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="VISA Configure Serial Port" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port"/>
				<Item Name="VISA Configure Serial Port (Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Instr).vi"/>
				<Item Name="VISA Configure Serial Port (Serial Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Serial Instr).vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
			</Item>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
