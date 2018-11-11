//设置窗口大小
window.external.call('setWindowSize', '647,400');
//设置窗口是否可Resize
window.external.call('enableResize', 'false');
//设置透明颜色
window.external.call('setTransparentColor', '8,8,8');
//设置窗口居中
window.external.call0('moveToCenter');

//使能标题栏的功能
Enable_MoveWindow = true;
Enable_Close      = true;
Enable_Maximize   = false;
Enable_Restore    = false;
Enable_Minimize   = true;