//垃圾代码全靠百度 ctrl +c ctrl +v，勿喷。0xss
#include <io.h>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
void getAllFile(string path, vector<string>& files)
{
    // 文件句柄
    long hFile = 0;
    // 文件信息
    struct _finddata_t fileinfo;

    string p;

    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            // 保存文件的全路径
            files.push_back(p.assign(path).append("\\").append(fileinfo.name));

        } while (_findnext(hFile, &fileinfo) == 0); //寻找下一个，成功返回0，否则-1

        _findclose(hFile);
    }
}
//path: 指定目录
//files: 保存结果
//fileType: 指定的文件格式，如 .jpg
void getAllFiles1(string path, vector<string>& files, string fileType) //获取指定格式的文件(不搜索子文件夹）
{
    // 文件句柄
    long hFile = 0;
    // 文件信息
    struct _finddata_t fileinfo;

    string p;

    if ((hFile = _findfirst(p.assign(path).append("\\*" + fileType).c_str(), &fileinfo)) != -1) {
        do {

            // 保存文件的全路径
            files.push_back(p.assign(path).append("\\").append(fileinfo.name));

        } while (_findnext(hFile, &fileinfo) == 0); //寻找下一个，成功返回0，否则-1

        _findclose(hFile);
    }
}
 void getAllFiles(string path, vector<string>& files, string fileType) {  //获取指定目录下的所有文件（搜索子文件夹）
    //文件句柄
    long hFile = 0;
    //文件信息
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
       // getAllFiles1(p.assign(path).append("\\").append(fileinfo.name), files, fileType);
        do {
            if (fileinfo.attrib == _A_SUBDIR) { //比较文件类型是否是文件夹
            
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) { 
                   files.push_back(p.assign(path).append("\\").append(fileinfo.name));
                    //递归搜索
                    getAllFiles1(p.assign(path).append("\\").append(fileinfo.name), files, fileType);
                    if ((fileinfo.attrib & _A_SUBDIR)) {
                        getAllFiles(p.assign(path).append("\\").append(fileinfo.name), files, fileType);
                    }
                }
            }
        
           
        } while (_findnext(hFile, &fileinfo) == 0); //寻找下一个，成功返回0，否则-1
        getAllFiles1(p.assign(path).append("\\").append(fileinfo.name), files, fileType);
        _findclose(hFile);
    }
    //getAllFiles(p.assign(path).append("\\").append(fileinfo.name), files, fileType);
}

 void getAllFiles2(string path, vector<string>& files) {  //获取指定目录下的所有文件（搜索子文件夹）
     // 文件句柄
     long  hFile = 0;
     //文件信息 
     struct _finddata_t fileinfo;
     string p;
     if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
     {
         do
         {
             if ((fileinfo.attrib & _A_SUBDIR))
             {
                 if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                 {
                     files.push_back(p.assign(path).append("\\").append(fileinfo.name));
                     getAllFile(p.assign(path).append("\\").append(fileinfo.name), files);
                     if ((fileinfo.attrib & _A_SUBDIR)) {
                         getAllFiles2(p.assign(path).append("\\").append(fileinfo.name), files);
                     }
                 }
             }
             else
             {
                 files.push_back(p.assign(path).append("\\").append(fileinfo.name));
             }
         } while (_findnext(hFile, &fileinfo) == 0);
         _findclose(hFile);
     }
 }

int main(int argc, char** argv){
    //FILE* fp = fopen("result.txt", "w");
    fstream  out_file("result.txt", ios::out| ios::trunc);
   string dic;
    vector<string> temp;
    string filename;
    string suffix;
    //string filename = "C:\\Program Files\\7-Zip";
    //string suffix = ".txt";
    string A;
        cout << "   循环输出指定目录的指定文件后缀输入：1  \n" <<"   循环输出指定目录包括子文件夹的指定文件后缀输入：2 \n"<<"   循环输出指定目录包括子文件夹的全部文件后缀输入：3\n"<<"   其它字符将输出指定目录全部文件后缀\n"<< endl;
        getline(cin, A);
        if (A=="1") {
            cout << "循环输出指定目录的指定文件后缀输入：1 " << endl;
            cout << "输入要遍历的目录 比如D:\\Pictures  : " << endl;
            getline(cin, filename);
            cout << "输入要遍历后缀 比如 .jpg   : " << endl;
            getline(cin, suffix);
            getAllFiles1(filename, temp, suffix);
            for (int i = 0; i < temp.size(); ++i)
            {
                cout << temp[i] << endl;
                dic = temp[i];
                out_file << dic << "\n";
            }
           
           
            out_file.close();
            return 0;
        }
        else if (A == "2") {

            vector<string> temps;
            cout << "输出指定目录包括子文件夹的全部指定后缀文件名  \n" << endl;
            cout << "输入要遍历的目录 比如D:\\Pictures  : " << endl;
            getline(cin, filename);
            cout << "输入要遍历后缀 比如 .jpg   : " << endl;
            getline(cin, suffix);
            getAllFiles1(filename, temps, suffix);
            for (int i = 0; i < temps.size(); ++i)
            {
                cout << temps[i] << endl;
                dic = temps[i];
                out_file << dic << "\n";
            }
            getAllFiles(filename, temp, suffix);
            for (int i = 0; i < temp.size(); ++i)
            {
                cout << temp[i] << endl;
                dic = temp[i];
                out_file << dic << "\n";
            }
            out_file.close();
        }
        else if (A == "3") {

           cout << "输出指定目录包括子文件夹的全部文件名\n" << endl;
           cout << "输入要遍历的目录 比如D:\\Pictures   : " << endl;
           getline(cin, filename);
           getAllFiles2(filename, temp);
            for (int i = 0; i < temp.size(); ++i)
            {
                cout << temp[i] << endl;
                dic = temp[i];
                out_file << dic << "\n";
            }
            out_file.close();
        }

        else {
            cout << "输出指定目录的全部文件名\n" << endl;
            cout << "输入要遍历的目录 比如D:\\Pictures   : " << endl;
                getline(cin, filename);
                getAllFile(filename, temp);
                for (int i = 0; i < temp.size(); ++i)
                {
                    cout << temp[i] << endl;
                    dic = temp[i];
                    out_file << dic << "\n";
        }
            return 0;

            out_file.close();
        }
        cout << "输出内容保存在当前目录的 result.txt 文件中 \n" << endl;
        cout << "按任意键结束程序 \n" << endl;
        getchar();
        return 0;
    };
