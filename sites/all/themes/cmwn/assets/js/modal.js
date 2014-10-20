(function($){$(function(){
	modal = {}
	modal.active = function(n,hideClose) {
		var _tabs = $('#modal-tabs');
		_tabs.find('li').removeClass('active').eq(n-1).addClass('active');
		if (hideClose) $('#modal-close-wrap').hide();
		else $('#modal-close-wrap').show();
	}
	
	modal.update = function(tabs) {
		if (tabs) {
			var _tabs = $('#modal-tabs');
			var _content = $('#modal-content-wrapper');
	
			$.each(tabs,function(n){	
				var _tab = $('<li></li>');
	
				if (tabs[n].href) {	
					_tab.addClass('active').append(tabs[n].title);		
					
					switch(tabs[n].href) {
						case '/user/register/child':
							$(".modal-content-bg").animate({"height":"476px"},350,function(){
								$(this).addClass("tabbed");
							});						
						break;
						
						case '/user/register/parent':
						case '/user/register/teacher':
							$(".modal-content-bg").animate({"height":"559px"},350,function(){
								$(this).addClass("tabbed");
							});						
						break;
					}
					
					_content.find('iframe').css({'visibility':'hidden'}).attr('src', tabs[n].href).load(function(){ $(this).css({'visibility':'visible'}); });
					$("#modal-tabs").fadeIn("slow");

				} else {	
					_tab.append(tabs[n].title);	
				}
	
				_tabs.find('ul').append(_tab);	
			});
		}
	}
	
	modal.create = function(url) {
		$('body').css({'overflow-x':'hidden'});

		var _background = $('<div id="modal-background" />');
		_background.css({
			'height':Math.max($(window).height(),$(document).height()),
			'left':0,
			'position':'absolute',
			'top':0,
			'width':Math.max($(window).width(),$(document).width()),
		});	
		
		var _window = $('<div id="modal-window" />');
		_background.append(_window);

		var _tabs = $('<div id="modal-tabs"><ul></ul></div>');
		_window.append(_tabs);

		var _content = $('<div id="modal-content-wrapper"><iframe src="' + url + '" allowtransparency="true" style="visibility:hidden;" onload="this.style.visibility=\'visible\';"></iframe><div class="modal-content-bg"></div></div>');
		_window.append(_content);

		var _close = $('<div id="modal-close-wrap"><div id="modal-close"></div></div>');
		_close.bind('click',function(){
			modal.hide();
		});
		_window.append(_close);

		$('body').append(_background);
		$('#modal-background').fadeIn("slow");
	}
	
	modal.hide = function() {
		$('#modal-background').fadeOut("slow",function() { $(this).remove(); });
		$('body').css({'overflow-x':'auto'});
	}
	
	modal.show = function(url,tabs) {
		modal.create(url);
		modal.update(tabs);
	}
	
	$('a[href="/register-choose"], a[href="/user/register"]').bind('click',function(){
		modal.show('/register-choose');
		return false;
	});
	
	$('.modal-registration-step-0 a.child').bind('click',function(){
		$("#modal-content-inside").fadeOut("slow",function() {
			$("#modal-content").addClass("tabbed");
			window.parent.modal.update([
				{'title':'<span>Step 1:</span> Enter Your Info', 'href':'/user/register/child'},
				{'title':'<span>Step 2:</span> Take the Interest Survey'},
				{'title':'<span>Step 3:</span> Get Your Parent\'s Approval'}
			]);
		});
		return false;
	});
	
	$('.modal-registration-step-0 a.parent').bind('click',function(){
		$("#modal-content-inside").fadeOut("slow",function() {
			$("#modal-content").addClass("tabbed");
			window.parent.modal.update([
				{'title':'<span>Step 1:</span> Enter Your Info', 'href':'/user/register/parent'},
				{'title':'<span>Step 2:</span> Security Questions'},
				{'title':'<span>Step 3:</span> Add Your Child'}
			]);
		});
		return false;
	});
	
	$('.modal-registration-step-0 a.teacher').bind('click',function(){
		$("#modal-content-inside").fadeOut("slow",function() {
			$("#modal-content").addClass("tabbed");
			window.parent.modal.update([
				{'title':'<span>Step 1:</span> Enter Your Info', 'href':'/user/register/teacher'},
			]);
		});
		return false;
	});

	$('#edit-terms-and-conditions-wrapper label').bind('mouseover',function(){
		$(this).parent().find('.description').fadeTo('fast',0,function(){
			$(this).css({'margin-top':-(($(this).height()+42)/2)+'px'});
			$(this).fadeTo('fast',1);
		});
		$('#modal-terms-and-conditions').show();
		$('#modal-terms-and-conditions').animate({'height':300},function(){$('#modal-terms-and-conditions .scroll').jScrollPane();});
	});

	$('#edit-terms-and-conditions-wrapper label').bind('mouseout',function(){
		$(this).parent().find('.description').fadeOut('fast');
	});

	$('#modal-terms-and-conditions .close a').bind('click',function(){
		$('#modal-terms-and-conditions').animate({'height':0},function(){$('#modal-terms-and-conditions').hide();});
		return false;
	});

});})(jQuery);

$(window).resize(function() {
	$("#modal-background").height($(window).height()).width($(window).width());
});