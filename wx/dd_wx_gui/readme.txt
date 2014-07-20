wx Version:	wxWidgets-3.0.1
IDE:	Code::Blocks 13.12 + Mingw-TDM-GCC-481

Change Note:
2014-07-20 Revision 11
	功能：从Input file copy一段data到Output file，Begin position指定 从
		Input file读取data的起始位置，Copy size指定从Begin position开始 总共
		copy到Output file的数据大小。
	已知问题：
		Begin position/Copy size 使用的控件是 wxSpinCtrl，它输入的是int类型，
		而Begin position/Copy size是long long int类型。
	