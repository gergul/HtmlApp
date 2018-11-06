//设置窗口大小
window.external.call('setWindowSize', '500,500');
//设置窗口是否可Resize
window.external.call('enableResize', 'false');
//设置透明颜色
window.external.call('setTransparentColor', '0,0,0');

//使能标题栏的功能
Enable_MoveWindow = true;
Enable_Close      = false;
Enable_Maximize   = false;
Enable_Restore    = false;
Enable_Minimize   = false;