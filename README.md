# Compiler-final-project 自製編譯器

利用 .l(lexer)、.y(parser)、c++ 製作的指令式計算機 
### 使用方法: 執行 [Main.cpp](https://github.com/ubin0914/Compiler-final-project/blob/master/Compiler/main.cpp)
### 實作語法
> any integer/double/boolean Constant value  
> any Variable name  
> \+ \- \* / **(次方) .(內積)  
> = += -= *= /= ++ --  
> < <= > >= == !=  
> type() abs() log() merge() len() (int)() (double)() (bool)()  
> ? : (三元運算子)  
> ( ) (括號運算子)  
> [ ] (取得陣列元素)  
> [:] (取子陣列)  
> { , , } (陣列宣告式)  
    
#### 詳細實作可直接參照程式碼  
* lexer.l: Regular Expression 關鍵字與符號等描述
* parser.y: Grammar 指令文法描述
* Constant.cpp: 數值之基本類別，定義 建構數值、數值運算、數值操作 等函式，供 parser.y 調用
* Variable.cpp: 自訂變數類別，提供建構函式，並新增至變數名字典
### 輸入範例
![image](https://user-images.githubusercontent.com/73873427/236663016-f40c2598-e9ac-40a3-b807-e46ff395b20e.png)
