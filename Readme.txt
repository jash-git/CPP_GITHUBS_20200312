C/C++領域的練手開源項目，小伙伴們接好CPP_GITHUBS(20200312)

資料來源:https://mp.weixin.qq.com/s?__biz=MzA3MTU1MzMzNQ==&mid=2247484944&idx=1&sn=8837e98d121a6c75e36de551f2189414&chksm=9f2a9e48a85d175e19961d0f89bf2e3cf6c90110c6a408848c951f2ad93a6ce5920a053e6271&scene=126&sessionid=1583983785&key=3da213d245c0d5c4105db8708d56875e7c958d7822d55c8cac0f24150a591d4e6cd6475d7be48fd257c7668cda5a45b6046a8b3744134ee6e30aaf43d9c6e4e39f595228317b5b57cf5872b839f782c6&ascene=1&uin=MjIwODk2NDgxNw%3D%3D&devicetype=Windows+10&version=62080079&lang=zh_TW&exportkey=AuZs1n8DbKdFIV%2FtMlEuPJo%3D&pass_ticket=XItwCcJzAR5Yaj6DjYe3DEYn48n84aDJTlwhfAmKN69S052IO7%2BwpOTJ94G4RIQq


01.Tinyhttpd ~ https://github.com/EZLippi/Tinyhttpd

項目簡介：Tinyhttpd是J. David Blackstone在1999年寫的一個不到500行的超輕量型Http Server，用來學習非常不錯，可以幫助我們真正理解服務器程序的本質。建議源碼閱讀順序為：main ->startup ->accept_request ->execute_cgi,通曉主要工作流程後再仔細把每個函數的源碼看一看。這500行代碼吃透了，C語言的功底就會大幅提升。


02.tmux ~ https://github.com/tmux/tmux

項目簡介：tmux一個炫酷的終端復用軟件，它提供了一個非常易於使用的命令行界面，可橫向和縱向分割窗口，窗格可以自由移動和調整大小，而且還可以通過交互式菜單來選擇窗口、會話及客戶端。類似的終端復用器還有GNU Screen。Tmux與它功能相似，但是更易用，也更強大。大名鼎鼎的阮一峰老師還寫過tmux的使用教程，大家也可以看一看


03.musikcube (Stream Server) ~ https://github.com/clangen/musikcube

項目簡介：musikcube是一個使用C ++編寫的跨平台，運行於終端上的音樂播放器。musikcube可以在Windows，macos和linux上輕鬆編譯和運行。它也可以在帶有raspbian的樹莓派上很好地運行，並且可以設置為流音頻服務器。炫酷得一腿。


04.MyTinySTL ~ https://github.com/Alinshans/MyTinySTL

項目簡介：很多人表示學完C++不知道用來幹什麼，我覺得學完C++的第一個練手的好機會那就是自己試著實現一個小型的STL庫。MyTinySTL的作者它就用C++11重新復寫了一個小型STL（容器庫＋算法庫）。代碼結構清晰規範、包含中文文檔與註釋，並且自帶一個簡單的測試框架，非常適合新手學習與參考！


05.muduo ~ https://github.com/chenshuo/muduo

項目簡介：muduo是一個基於Boost庫實現的現代C++高並發網絡庫，由陳碩大神編寫。它一個高質量的事件驅動型的網絡庫，其核心代碼不超過4500行，使用non-blocking IO(IO multiplexing)+ one loop per thread模型，適合開發Linux下的多線程服務端應用程序，通過閱讀源碼還可學習到C++語言、Linux網絡編程等後端知識。


06.CppNet ~ https://github.com/caozhiyi/CppNet

項目簡介：CppNet一個封裝在TCP協議上的Proactor模式multi-thread網絡庫。包含OS接口調用、回調處理、定時器、緩存管理等，這裡有從操作系統到應用層的所有網絡細節，便於初學者學習和實踐。