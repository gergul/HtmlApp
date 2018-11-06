//设置窗口大小
window.external.call('setWindowSize', '800,600');
//设置窗口是否可Resize
window.external.call('enableResize', 'false');
//设置透明颜色
window.external.call('setTransparentColor', '255,255,255');
//窗口的初始位置
//window.external.call('moveTo', '0,0');

//使能标题栏的功能
Enable_MoveWindow = true;
Enable_Close      = false;
Enable_Maximize   = false;
Enable_Restore    = false;
Enable_Minimize   = false;