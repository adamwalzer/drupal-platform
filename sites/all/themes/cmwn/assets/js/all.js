$(function(){

	/* 1.4 global */


  $('#whiteboard-tab form').submit(function(){
    $('#whiteboard-tab form button').attr('disabled', 'disabled');
  });

	jQuery.extend(Tipped.Skins,{
		'cmwn':{
			background:'#ffffff',
			border:{
				color:'#54c2f2',
				size:1
			},
			closeButtonSkin:'dark',
			radius:{
				size:6
			},
			shadow:{
				blur:12,
				color:'#000000',
				offset:{
					x:0,
					y:0
				},
				opacity:.06
			}
		}
	});

	$.extend($.modal.defaults,{
		closeClass:'close',
		closeHTML:'<a href="#">Close</a>',
		opacity:66,
		overlayClose:true,
		position:[180,]
	});

	/* 1.4 account */

	var modal_account_delete = $(':[id^="account-delete"]');
	var modal_account_delete_trigger = $(':[data-modal^="account-delete"]');;

	if (modal_account_delete.length == 1 && modal_account_delete_trigger.length == 1) {
		modal_account_delete_trigger.bind('click',function(){
			Processing.show();
			Tipped.create(
				'#v2',
				modal_account_delete.attr('id'),{
					'closeButton':true,
					'hideOn':false,
					'hook':{
		  				'target':'topmiddle',
		  				'tooltip':'topmiddle'
					},
					'inline':true,
					'onHide':function(){
						Tipped.remove('#v2');
						Processing.hide();
					},
					'skin':'cmwn',
					'stem':false
				}
			).show();
			return false;
		});
		modal_account_delete.find('button[type="button"]').bind('click',function(){
			Tipped.remove('#v2');
			Processing.hide();
			return false;
		});
	}


  //UI Refresh toggle sidebar
  var sidebar_toggling = false;
  $('#v2 div.sidebar-toggle').click(function(){
    var toggle_btn = $(this);
    if(!sidebar_toggling){
      switch(toggle_btn.hasClass('hide')){
        case true:
          sidebar_toggling = true;
          $('.sidebar-profile').animate({
            width: 0,
            right: 0
          }, 0, 'linear',function(){
            $(this).addClass('hidden').removeClass('visible');//sidebar-profile
            toggle_btn.addClass('show').removeClass('hide');
            sidebar_toggling = false;
          });


          $(this).animate({
            right: -40
          }, 0, 'linear',function(){

          });

          break;
        default://show
          sidebar_toggling = true;
          $('.sidebar-profile').animate({
            width: 240,
            right: -240
          }, 0, 'linear',function(){
            $(this).addClass('visible').removeClass('hidden');//sidebar-profile
            toggle_btn.addClass('hide').removeClass('show');
            sidebar_toggling = false;
          });


          $(this).animate({
            right: 0
          }, 0, 'linear',function(){

          });

          break;
      }

    }

  });

  //school dashboard tabs
  $('#school-dashboard-tabs').tabs({collapsible: true});
  //UI Refresh Whiteboard/Newsfeed tabs
  $('#whiteboard-profile-tabs').tabs({collapsible: true});
  //UI Refresh Call Monitor
  $('span.call-monitor').click(function(){

  if($("#mainpanel li a.subpanel_toggle").next(".subpanel").is(':visible')){ //If subpanel is already active...
      $("#mainpanel li a.subpanel_toggle").next(".subpanel").hide(); //Hide active subpanel
      $("#drupalchat li a").removeClass('active'); //Remove active class on the subpanel trigger
  }
  else { //if subpanel is not active...
      $(".subpanel").hide(); //Hide all subpanels
      $("#mainpanel li a.subpanel_toggle").next(".subpanel").toggle(); //Toggle the subpanel to make active
      $("#drupalchat li a").removeClass('active'); //Remove active class on all subpanel trigger
      $("#mainpanel li a.subpanel_toggle").toggleClass('active'); //Toggle the active class on the subpanel trigger
      // Chat box functions
      var isTextarea = $("#mainpanel li a.subpanel_toggle").next(".subpanel").children(".chatboxinput").children(".chatboxtextarea");
      if (isTextarea.length > 0) {
      	isTextarea[0].focus();
      	$("#mainpanel li a.subpanel_toggle").next(".subpanel").children(".chatboxcontent").scrollTop($("#mainpanel li a.subpanel_toggle").next(".subpanel").children(".chatboxcontent")[0].scrollHeight);
      }
  }

    //$(".subpanel").hide();$("#drupalchat li a").removeClass('active');
  });


  $('.block.links.index  > .content > .section > div.item-list li > a.active').parent().addClass('active');
  $('.block.links.index  > .content > .section > div.item-list > ul > li > div.item-list').toggle();
  $('.block.links.index  > .content > .section > div.item-list > ul > li > a.toggle').click(function(){
    $(this).siblings('div.item-list').toggle().toggleClass('visible');
    $(this).toggleClass('collapse');
  });
  $('.block.links.index  > .content > .section > div.item-list > ul > li > div.item-list:hidden').each(function(){
    if($(this).find('a.active').length > 0){
      $(this).show();
    }
  });




/*
  //school dashboard upload file ui
  var SITE = SITE || {};

  SITE.fileInputs = function() {
    var $this = $(this),
        $val = $this.val(),
        valArray = $val.split('\\'),
        newVal = valArray[valArray.length-1],
        $button = $this.parent().siblings('.button'),
        $fakeFile = $this.siblings('.file-holder');
    if(newVal !== '') {
      $button.text('Spreadsheet Uploading...');
      if($fakeFile.length === 0) {
        //$button.after('<span class="file-holder">' + newVal + '</span>');
      } else {
        $fakeFile.text(newVal);
      }
    }
  };

  $('#edit-school-import-wrapper input[type=file]').bind('change focus click', SITE.fileInputs);
*/

  //teacher profile page, flip overlay on class students
  var class_modal_tipped = $('#v2 .column.content .block.teacher-class.browse .content .section .items .item');

  if (class_modal_tipped.length > 0) {
  	class_modal_tipped.each(function(){
  		var source = $(this);
  		var content = $(this).find('.block.modal.flips.description');
  		Tipped.create(
  			source,
  			content.attr('id'),{
  				'hook':{
  	  				'target':'rightmiddle',
  	  				'tooltip':'leftmiddle'
  				},
  				'inline':true,
  				'skin':'cmwn'
  			}
  		);
  	});
  }

//ui refresh - greater than 3 likes overlay
//teacher profile page, flip overlay on class students
  var likes_modal_tipped = $('em.modal-tip');

  if (likes_modal_tipped.length > 0) {
  	likes_modal_tipped.each(function(){
  		var source = $(this);
  		var content = $(this).find('div.item-list-likes');
  		Tipped.create(
  			source,
  			content.attr('id'),{
  				'hook':{
  	  				'target':'rightmiddle',
  	  				'tooltip':'leftmiddle'
  				},
  				'inline':true,
  				'skin':'cmwn'
  			}
  		);
  	});
  }

  //ui refresh - profile sidebar links accordian
  //$('ul.profile-links').accordion();
  //tooltips
  //$('span.call-monitor').qtip();
  //$('[title]').qtip();







	/* 1.4 feed */


    //friend feed
    $('.section.friend-feed .scroll').load('/cmwn_feed/friend/' + $('.section.friend-feed .scroll').attr('u'), function(){
      //set height
      var ffh = 0;//friend feed height
      $('.section.friend-feed .scroll .item:lt(12)').each(function() {//set to height of first 12 items
         ffh += $(this).height() + 12;//top and bottom padding factored in.
      });
      $('.section.friend-feed .items .scroll').height(ffh);//make room for pager

      //institute scrolling thingy
      //$('#v2 .block.feed.index .content .section .items .scroll').jScrollPane({'verticalGutter':6});

      //start lazy loader

      $('.section.friend-feed div.jscrolldiv').jscroll({
        loadingHtml: '<img src="loading.gif" alt="Loading" /> Loading...',
        nextSelector: 'li.pager-next a',
        padding: 50,
        callback:function(){},
      });
    });

    // flip feed
    $('.section.flip-feed .scroll').load('/cmwn_feed/flip', function(){
      //set height
      var ffh = 0;//friend feed height
      $('.section.flip-feed .scroll .item:lt(5)').each(function() {//set to height of first 12 items
         ffh += $(this).height() + 12;//top and bottom padding factored in.
      });
      $('.section.flip-feed .items .scroll').height(ffh);//make room for pager

      //institute scrolling thingy
      //$('#v2 .block.feed.index .content .section .items .scroll').jScrollPane({'verticalGutter':6});

      //start lazy loader

      $('.section.flip-feed div.jscrolldiv').jscroll({
        loadingHtml: 'Loading...',
        nextSelector: 'li.pager-next a',
        padding: 50,
        callback:function(){},
      });
    });

	/* 1.4 flips */

	var modal_flips_interests = $('#flips-interests');
	var modal_flips_interests_trigger = $('#v2 .block.flips.browse .header .section.form a.filter');

	if (modal_flips_interests.length == 1) {
		Tipped.create(
			modal_flips_interests_trigger,
			modal_flips_interests.attr('id'),{
				'hook':{
					'target':'bottommiddle',
					'tooltip':'topmiddle'
				},
				'inline':true,
				'skin':'cmwn'
			}
		);
	}

	$('#v2 .column.content .block.flips.browse .content .section .items').not('.games').isotope({
		animationEngine:'jquery',
		itemSelector:'.item'
	});

	$('#flips-interests a').bind('click',function(){
		var source = $(this);
		$('#v2 .column.content .block.flips.browse .content .section .items').isotope({
			filter:source.data('filter')
		});
		return false;
	});

	var modal_tipped = $('#v2 .column.content .block.flips.browse .content .section .items .item');

	if (modal_tipped.length > 0) {
		modal_tipped.each(function(){
			var source = $(this);
			var content = $(this).find('.block.modal.flips.description');
			Tipped.create(
				source,
				content.attr('id'),{
					'hook':{
		  				'target':'rightmiddle',
		  				'tooltip':'leftmiddle'
					},
					'inline':true,
					'skin':'cmwn'
				}
			);
		});
	}

	var modal_safety_tips = $(':[id^="safety-tips"]');

	if (modal_safety_tips.length == 1) {
		Processing.show();
		Tipped.create(
			'#v2',
			modal_safety_tips.attr('id'),{
				'closeButton':false,
				'hideOn':false,
				'hook':{
	  				'target':'topmiddle',
	  				'tooltip':'topmiddle'
				},
				'inline':true,
				'onHide':function(){
					Tipped.remove('#v2');
					Processing.hide();
				},
				'skin':'cmwn',
				'stem':false
			}
		).show();
		modal_safety_tips.find('.button').bind('click',function(){
			Tipped.remove('#v2');
			Processing.hide();
			return false;
		});
	}

	$('#v2 .block.flips.action .content .section.step .cms .more a').bind('click',function(){
		var source = $(this);
		var target = source.parent().prev();
		if (target.hasClass('collapsed')) {
			target.show().removeClass('collapsed');
			source.html('Hide Description').addClass('close');
		} else {
			target.hide().addClass('collapsed');
			source.html('Read More').removeClass('close');
		}
		return false;
	});

	$('#v2 .block.flips.action .content .section.step .cms .start a').bind('click',function(){
		$('#v2 .block.flips.action .content .section.step.n1').removeClass('disabled');
		$('#v2 .block.flips.action .content .section.step.n1').find('button,input,select,textarea').removeAttr('disabled').removeClass('disabled');
		return false;
	});

	$('#v2 .block.flips.action .content .section.step.disabled').each(function(){
		var source = $(this);
		source.find('button,input,select,textarea').attr('disabled','disabled').addClass('disabled');
	});

	$('#v2 .block.flips.action .content .section.step:last-child').each(function(){
		var source = $(this);
		source.find('input[type="submit"]').val('Finish');
	});

	/* 1.4 friends */

	var modal_friends_interests = $('#friends-interests');
	var modal_friends_interests_trigger = $('#v2 .block.friends.browse .header .section.form a.filter');

	if (modal_friends_interests.length == 1) {
		Tipped.create(
			modal_friends_interests_trigger,
			modal_friends_interests.attr('id'),{
				'hook':{
					'target':'bottommiddle',
					'tooltip':'topmiddle'
				},
				'inline':true,
				'skin':'cmwn'
			}
		);
	}

	var modal_friends_remove = $('#friends-remove');
	var modal_friends_remove_trigger = $('#v2 .block.friends.browse .content .items .item .actions .remove');

	if (modal_friends_remove.length > 0 && modal_friends_remove_trigger.length > 0) {
		modal_friends_remove_trigger.each(function(){
			var source = $(this);
			var href = source.attr('href');
			source.bind('click',function(){
				Processing.show();
				Tipped.create(
					'#v2',
					modal_friends_remove.attr('id'),{
						'closeButton':true,
						'hideOn':false,
						'hook':{
			  				'target':'topmiddle',
			  				'tooltip':'topmiddle'
						},
						'inline':true,
						'onHide':function(){
							Tipped.remove('#v2');
							Processing.hide();
						},
						'skin':'cmwn',
						'stem':false
					}
				).show();
				modal_friends_remove.find('.button.remove').attr('href',href);
				return false;
			});
			modal_friends_remove.find('.button.cancel').bind('click',function(){
				Tipped.remove('#v2');
				Processing.hide();
				return false;
			});
		});
	}

	/* 1.4 links */

	var modal_links_interests = $('#links-interests');
	var modal_links_interests_trigger = $('#v2 .block.links.index .content .section ul li:last-child a[href="#"]');

	modal_links_interests_trigger.css({'cursor':'default'}).bind('click',function(){
		return false;
	});

	if (modal_links_interests.length == 1) {
		Tipped.create(
			modal_links_interests_trigger,
			modal_links_interests.attr('id'),{
				'hook':{
					'target':'rightmiddle',
					'tooltip':'leftmiddle'
				},
				'inline':true,
				'skin':'cmwn'
			}
		);
	}

	/* 1.4 profile */

	var modal_child_pending_approval = $(':[id^="profile-pending-approval"]');

	if (modal_child_pending_approval.length == 1) {
		Processing.show();
		Tipped.create(
			'#v2',
			modal_child_pending_approval.attr('id'),{
				'closeButton':false,
				'hideOn':false,
				'hook':{
					'target':'topmiddle',
					'tooltip':'topmiddle'
				},
				'inline':true,
				'onHide':function(){},
				'skin':'cmwn',
				'stem':false
			}
		).show();
	}

	/* 1.4 videos */

	$('#v2 .block.videos.index .content .section.filter ul li a').bind('click',function(){
		var source = $(this);
		var n = source.parent().data('n');
		var target = $('#v2 .block.videos.index .content .section.panel[data-n="'+n+'"]');
		$('#v2 .block.videos.index .content .section.filter ul li').removeClass('active');
		$('#v2 .block.videos.index .content .section.panel').hide();
		source.parent().addClass('active');
		target.show();
		return false;
	});

	$('#v2 .block.videos.index .content .section.panel .items .item a').bind('click',function(){
		var source = $(this);
		$.modal('<iframe src="' + source.attr('href') + '" height="581" width="789" style="border:none;overflow:hidden;">', {
			'closeHTML':'',
			'minHeight':581,
			'minWidth':789
		});
		return false;
	});

	/* 1.4 whiteboard */


  //disable deleting video links during video post.
  $('.whiteboard.index button').click(function(){
    $('a.delete').click(function(){
      //$(this).hide
      return false;
    });
    $('a.delete').fadeOut(500);
  });

	$('#v2 .whiteboard .create .form input[type="file"]').bind('change',function(){
		var source = $(this);
		var target = $('#v2 .whiteboard .create .form span.file');
		target.prev().removeClass('with-file');
		target.text('');
		target.next().find('span').text('Add Media');
		if (source.val() != '') {
			var allowed = ['gif','jpg','JPG','jpeg','png','avi','flv','m4v','mov','MOV','mp4','MP4','mpg','MPG','wmv','WMV','wma','WMA'];
			var name = source.val().replace("C:\\fakepath\\", "");
			var extension = name.split('.').pop();
			if (jQuery.inArray(extension, allowed) != -1) {
				target.prev().addClass('with-file');
				target.text('File: ' + name);
				target.next().find('span').text('Change');
			} else {
				target.prev().addClass('with-file');
				target.text(extension + ' is not a supported file format.');
				target.next().find('span').text('Change');
				source.val('');
			}
		}
		return false;
	});

	var modal_tipped = $('#v2 .block.whiteboard.index a.delete, #v2 .block.whiteboard.index a.report');

	if (modal_tipped.length > 0) {
		modal_tipped.each(function(){
			var source = $(this);
			Tipped.create(
				source,
				'<div class="block tipped">'+source.attr('title')+'</div>',{
					'hook':{
		  				'target':'leftmiddle',
		  				'tooltip':'rightmiddle'
					},
					'offset':{
						'x':-14,
						'y':0
					},
					'skin':'cmwn'
				}
			);
		});
	}

	var modal_post_pending_moderation = $('#post-pending-moderation');

	if (modal_post_pending_moderation.length == 1) {
		Processing.show();
		Tipped.create(
			'#v2',
			modal_post_pending_moderation.attr('id'),{
				'closeButton':true,
				'hideOn':false,
				'hook':{
					'target':'topmiddle',
					'tooltip':'topmiddle'
				},
				'inline':true,
				'onHide':function(){
					Tipped.remove('#v2');
					Processing.hide();
				},
				'skin':'cmwn',
				'stem':false
			}
		).show();
	}

  /* Moderation Dashboard */



$('.view-moderation-avatars .views-field-title a, .views_view__moderation .views-field-title a, .view-moderation-denied .views-field-title a, .view-moderation-approved .views-field-title a, .view-moderation-comments .views-field-view-comment a').each(function(){
  var ton = false;
  $(this).click(function() {
    $('tr.mod-ajax').remove();
    $('#mod-this').remove();

    var $link = $(this);
    $('<a name="mod-this" id="mod-this" />').insertAfter($(this).parent().parent());
    $('<td colspan="4"></td>').insertAfter('#mod-this')
        .load($link.attr('href') + ' #v2', function(){
          $('html, body').animate({scrollTop: $('#mod-this').offset().top }, 500);

          $('#cmwn-moderation-form #edit-cancel').click(function(){
            $(this).parents('tr.mod-ajax').remove();
            return false;
          });
          
        }).wrap('<tr class="mod-ajax"></tr>');
        return false;
  });
});






  /* End Moderation Dashboard */


	/* 1.4 */

	$(window).bind('resize',function(){

		Processing.resize();

	});

});

Processing = {}

Processing.hide = function() {

	var container = $('#processing');

	container.remove();

	$('body').css({'overflow':'auto'});

}

Processing.show = function() {

	Processing.hide();

	var container = $('<div id="processing" />');

	$('body').css({'overflow':'hidden'});

	container.css({
		'height':Math.max($(window).height(),$(document).height()),
		'left':0,
		'position':'absolute',
		'top':0,
		'width':Math.max($(window).width(),$(document).width()),
		'z-index':999
	});

	window.scrollTo(0,0);

	$('body').append(container);

}

Processing.resize = function() {

	var container = $('#processing');

	if (container.length == 1) {
		container.css({
			'height':Math.max($(window).height(),$(document).height()),
			'width':Math.max($(window).width(),$(document).width())
		});
	}

}
