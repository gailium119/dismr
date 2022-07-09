# dismr
DISM for ReactOS. Only support add package now and doesn't support drivers.

Note: ROS hive is not compatible with Windows host. 

Use this image to test:https://www.mediafire.com/file/56016xtgkzj4a5b/ReactOS.wim/file (Apply first)

And use this package to test:https://www.mediafire.com/file/5ycol0vdazs11l4/testpkg.zip/file (Unzip first)

E.g. ReactOS.wim applied to E:\ , package unzipped to D:\1

dismr /image:E:\ReactOS /Add-Package:D:\1\ROS-Test-Package~31bf3856ad364e35~amd64~~10.0.22621.1.rum 

(Require TrustedInstaller on Windows Host)
