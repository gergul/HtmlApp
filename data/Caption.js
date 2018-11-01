
/*
class = Title Close Maximize Restore Minimize
*/

/* 以下是使能设置变量：undefined 或 true时可用；false时不可用
Enable_MoveWindow 
Enable_Close 
Enable_Maximize 
Enable_Restore 
Enable_Minimize
*/

$(function(){
	$('.Title').each(function(index){
		if (typeof Enable_MoveWindow == 'undefined' || Enable_MoveWindow) {
			$(this).on('mousedown',function(event){
				window.external.call('onMouseDownCaption', '');
				event.preventDefault();
			});
		}
		
		if (typeof Enable_Maximize == 'undefined' || Enable_Maximize) {
			$(this).on('dblclick',function(event){
				window.external.call('onDbClickHtmlCaption', '');
				
				$('.Maximize').each(function(index){
					$(this).toggle();
				});
				
				$('.Restore').each(function(index){
					$(this).toggle();
				});
				
				event.preventDefault();
			});
		}
	});
});

$(function(){
	if (typeof Enable_Close == 'undefined' || Enable_Close) {
		$('.Close').each(function(index){
			$(this).on('click',function(event){
				window.external.call('onClickClose', '');
				event.preventDefault();
			});
		});
	}
});

$(function(){
	if (typeof Enable_Maximize == 'undefined' || Enable_Maximize) {
		$('.Maximize').each(function(index){
			$(this).show();
			
			$(this).on('click',function(event){
				window.external.call('onClickMax', '');
				
				$('.Maximize').each(function(index){
					$(this).hide();
				});
				
				$('.Restore').each(function(index){
					$(this).show();
				});
				
				event.preventDefault();
			});
		});
	}
});

$(function(){
	if (typeof Enable_Restore == 'undefined' || Enable_Restore) {
		$('.Restore').each(function(index){
			$(this).hide();
			
			$(this).on('click',function(event){
				window.external.call('onClickRestore', '');
				
				$('.Maximize').each(function(index){
					$(this).show();
				});
				
				$('.Restore').each(function(index){
					$(this).hide();
				});
				
				event.preventDefault();
			});
		});
	}
});

$(function(){
	if (typeof Enable_Minimize == 'undefined' || Enable_Minimize) {
		$('.Minimize').each(function(index){
			$(this).on('click',function(event){
				window.external.call('onClickMin', '');
				event.preventDefault();
			});
		});
	}
});
	