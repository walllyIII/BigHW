#define _CRT_SECURE_NO_WARNINGS
#include"../include/exe_running.h"
using namespace std;
int main()
{
	st_CheckExec example_set[] = {
		/* 直接运行，正确 */
		{"D:\\25261-term\\参考exe\\第03模块-循环-九九乘法表.exe", "第03模块-循环-九九乘法表.exe", 1024, 1},
		/* 直接运行，超长错误 */
		{"D:\\25261-term\\参考exe\\第03模块-循环-九九乘法表.exe", "第03模块-循环-九九乘法表.exe", 128, 1},
		/* 管道方式运行，正确 */
		{"D:\\25261-term\\get_input_data.exe D:\\25261-term\\测试数据\\3-b3-pipe-data.txt [3-b3-22] | D:\\25261-term\\参考exe\\3-b3-demo-浮点数分解.exe","3-b3-demo-浮点数分解.exe", 256, 3},
		/* 重定向方式运行，正确 */
		{"D:\\25261-term\\参考exe\\3-b3-demo-浮点数分解.exe < D:\\25261-term\\测试数据\\3-b3-09.txt","3-b3-demo-浮点数分解.exe", 256, 3},
		/* 命令行参数方式运行（一重循环改进版，10秒以内） */
		{"D:\\25261-term\\参考exe\\1953-多种解.exe --3", "1953-多种解.exe", 30720, 20},
		/* 命令行参数方式运行（一重循环基本型，20秒以上），超长错误 */
		{"D:\\25261-term\\参考exe\\1953-多种解.exe --1", "1953-多种解.exe", 1024, 10},
		/* 命令行参数方式运行（一重循环基本型，20秒以上），超时错误 */
		{"D:\\25261-term\\参考exe\\1953-多种解.exe --1", "1953-多种解.exe", 30720, 3},
		/* 直接运行，显示菜单后等待输入，用正常方式执行会出现死循环错误（15秒后callback中taskkill） */
		{"D:\\25261-term\\参考exe\\1953-多种解.exe", "1953-多种解.exe", 30720, 10},
	};

	for (int i = 0; i < sizeof(example_set)/sizeof(st_CheckExec); i++) {
		/* 执行一个命令 */
		cout << endl << "--------------------------------------------" << endl;
		cout << "运行命令：" << example_set[i].get_full_cmd_exec() << endl;
		example_set[i].running();

		cout << "程序状态：" << example_set[i].get_errno() << endl;
		cout << "运行时间：" << example_set[i].get_running_time() << endl;

		/* 正确结束则打印输出内容 */
		if (example_set[i].get_errno() == CheckExec_Errno::ok) {
			cout << "程序输出：" << endl << example_set[i].msg.str() << endl << endl;
		}
		else {
			cout << "程序已输出长度：" << example_set[i].msg.str().length() << endl << endl;
		}
		cout << "--------------------------------------------" << endl;
	}

	return 0;
}
