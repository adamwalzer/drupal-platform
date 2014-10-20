jQuery(function($) {
  function handleConsoleLogging() {
    if (typeof console == 'undefined' || typeof console.log != 'function') {
      console = {
        log: function(){}
      };
    }
  }
  function initMenu() {
    var megamenuMouseOut = function (e) {
      if (!$(e.relatedTarget).is('.megamenu *, .megamenu')) {
        $('.main-nav .menu a').removeClass('hover');
        $(this).hide();
        $(this).unbind('mouseout', megamenuMouseOut);
      }
    }
    var offsets = {
        mlid_1478: 0,
        mlid_446: 0,
        mlid_447: 0,
        mlid_448: 0,
        mlid_481: -415
    };
    $('.main-nav > .menu-name-primary-links > .menu > li > a').mouseover(function(e){
      var menu_id = false;
      var classes = $(this).parents('li.leaf').attr('class').split(/\s+/);
      for (var str in classes) {
        if (typeof classes[str] == 'string' && classes[str].indexOf('menu-mlid-') === 0) {
          menu_id = classes[str].substring(10);
        }
      }
      $('.megamenu').hide();
      if (menu_id !== false) {
        $(this).addClass('hover');
        var megamenu = $('.megamenu.menu-mlid-'+menu_id);
        megamenu.css({left: $(this).position().left - $('.megamenu-wrap').position().left + offsets['mlid_'+menu_id]});
        megamenu.children('.white').css({width:$(this).width() - 9, marginLeft: -offsets['mlid_'+menu_id] + 6});
        if ($.browser.msie && $.browser.version == '7.0') {
          megamenu.children('.white').css({marginLeft: -offsets['mlid_'+menu_id] -6});
        }
        megamenu.show();
      }
    });
    $('.main-nav > .menu-name-primary-links > .menu > li > a').mouseout(function(e){
      $('.megamenu').unbind('mouseout', megamenuMouseOut);
      if ($(e.relatedTarget).is('.megamenu *')) {
        $(e.relatedTarget).parents('.megamenu').mouseout(megamenuMouseOut);
      } else if ($(e.relatedTarget).is('.megamenu')) {
        $(e.relatedTarget).mouseout(megamenuMouseOut);
      } else {
        $('.main-nav .menu a').removeClass('hover');
        $('.megamenu').hide();
      }
    });
  }
  function initExtLinks() {
    $('a[rel=external]').click(function(e){
      e.preventDefault();
      window.open($(this).attr('href'));
    });
  }
  function initTooltips() {
    /*$('.social a[title]').tooltip({
      effect:'slide',
      offset:[8,18]
    });*/
    $('.interests a[title]').tooltip({
      effect:'slide',
      offset:[-40,18]
    });
  }
  function initSponsorsScrollable() {
    $('.bottom-content .view-sponsors').scrollable({
      circular: true,
      next: '.controls-sponsors .next',
      prev: '.controls-sponsors .prev'
    }).autoscroll({
      autoplay: true,
      interval: 5000
    });
  }
  function initSearchBox() {
    $('#edit-search-block-form-1').focus(function(){
      $(this).val() == 'Search' ? $(this).val('') : null;
    });
  }
  handleConsoleLogging();
  initMenu();
  initExtLinks();
  initSearchBox();
  if ($.tools) {
    initSponsorsScrollable();
    initTooltips();
  }
  $(window).bind("resize", function(){
    if($(window).width() <= 2000){
      $('.view-homepage-slideshow').addClass("alt");
    }
    else{
      $('.view-homepage-slideshow').removeClass("alt");
    }
  });
  $("img[rel='rollover']").css('cursor', 'pointer');
  $("img[rel='rollover']").hover(
    function() {
      this.src = this.src.replace("_off", "_on");
    },
    function() {
      this.src = this.src.replace("_on", "_off");
    }
  );
});

jQuery.expr[':'].focus = function( elem ) {
  return elem === document.activeElement && ( elem.type || elem.href );
};