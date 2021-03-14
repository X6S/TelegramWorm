# Telegram-worm


No extra libs are used, works with unicode.

1. Check Telegram path exist
2. Check if process Telegram.exe is running
3. If not, start Telegram.exe, sleeps for 30 second
4. Check process Telegram.exe
5. If running, spreader gets GEO of current computer on site: http://api.wipmania.com/ (blocked by some dns adblockers, recommend changing)
- For example if country is RU, message will be: "Лучшее фото ) link"

6. Sets Clipboard data with message generated with GEO + your link "Лучшее фото ) link"
7. If ok, it sets windows out box, so user won't see the Telegram window anymore
8. Setfocus on Telegram window
9. Click crtl + menu + home ( it will focus the first convo in list )
10. Goes into for loop + presses ctrl + TAB (it select new convo), since right now there is no option to calculate how many convos it will spam all after each other for the time you config, in KillThread is Sleep(10000); // 10 seconds
11. Stimulaty ctrl +v ( paste ) as our message is in clipboard it will paste it in convo window + enter enter 3 times ( on slow computer it takes a bit longer till you see confirm )

A lot can be changed, people can learn from it, have fun.

"For Educational Purposes Only" xd
