<?php include 'page/header.tpl.php'; ?>
  </div>
  <?php if ($messages) : ?>
  <div class="skin-wrap">
    <div class="section-wrap section-messages">
      <?php print $messages; ?>
    </div>
  </div>
  <?php endif; ?>
  <div style="background:url(<?php print $theme_path; ?>/assets/img/new-hp/signin.jpg) center top no-repeat;height:406px;width:100%;left:50%;margin-bottom:-356px;"></div>
  <div class="skin-wrap <?php print $skin_class; ?>" style="position:relative;width:1024px;height:357px;margin:0 auto;background:none;top:-50px;">
    <div class="arrow" style="background:url(<?php print $theme_path; ?>/assets/img/sprite.png) left -4316px no-repeat;height:149px;width:70px;position:absolute;top:-87px;left:855px;"></div>
    <div class="campaign-wrap">
      <div class="campaign">
      <?php echo $campaign; ?>
      </div>
      <div class="controls-homepage-slideshow">
        <a class="prev browse left"></a>
        <a class="next browse right"></a>
      </div>
    </div>
    <div class="homepage-user">
      <?php if ($user->uid == 0) : ?>
        <img style="position:absolute;top:30px;left:748px;" src="<?php print $theme_path; ?>/assets/img/new-hp/ready-to-change.png" />
        <a href="/register-choose"><img style="position:absolute;top:120px;left:742px;" rel="rollover" src="<?php print $theme_path; ?>/assets/img/new-hp/start-now_off.png" /></a>
        <img style="position:absolute;top:196px;left:748px;" src="<?php print $theme_path; ?>/assets/img/new-hp/already-changing.png" />
      <?php echo drupal_get_form('user_login'); ?>
      <?php else : ?>
        <img style="position:absolute;top:30px;left:748px;" src="<?php print $theme_path; ?>/assets/img/new-hp/youre-logged-in.png" />
        <a href="/user"><img style="position:absolute;top:103px;left:742px;" rel="rollover" src="<?php print $theme_path; ?>/assets/img/new-hp/return-to-profile_off.png" /></a>
        <img style="position:absolute;top:248px;left:748px;" src="<?php print $theme_path; ?>/assets/img/new-hp/see-you-again.png" />
        <a href="/logout"><img style="position:absolute;top:196px;left:748px;" rel="rollover" src="<?php print $theme_path; ?>/assets/img/new-hp/logout_off.png" /></a>
      <?php endif; ?>
    </div>
  </div>
  <div class="skin-wrap <?php print $skin_class; ?>">
    <div class="section-wrap">
      <div class="left">
        <div class="left">
          
          <img src="<?php print $theme_path; ?>/assets/img/new-hp/partners.png" />
          <div style="position:relative;">
          <?php echo views_embed_view('sponsors', 'default'); ?>
          </div>
          
          <?php if(false):?>
          <div class="social" style="margin:20px 0 0 0;">
            <a href="http://www.facebook.com/ChangeMyWorldNow" class="facebook" title="Friend us on Facebook">Facebook</a>
            <a href="http://twitter.com/CMyWorldNow" class="twitter" title="Follow us on Twitter">Twitter</a>
          </div>
          <?php endif;?>
          <div class="footer_utilities">
          <?php print $footer_utilities; ?>
          </div>
        </div>
        <div class="right">
          
          
          <script type="text/javascript">
          
          
          jQuery(function($){
            $('#edit-name-wrapper input, #edit-pass-wrapper input').each(function(){
              var $this = $(this);
              setInterval(function(){
                if ($this.is(':focus') || $this.val() != '') {
                  $this.prev('label').css('color', '#fff');
                } else {
                  $this.prev('label').css('color', '#bfbfbf');
                }
              }, 100);
            });
            $('.view-homepage-slideshow').scrollable({
              circular: true,
              next: '.controls-homepage-slideshow .next',
              prev: '.controls-homepage-slideshow .prev'
            }).autoscroll({
              autoplay: true,
              interval: 10000
            });
          });
          
          </script>

      </div>
      <div class="right">
       <img src="<?php print $theme_path; ?>/assets/img/new-hp/contact-us.png" />
          <p style="margin:10px 0 0 0"><a style="font-weight:bold;color:#848077;" href="mailto:info@changemyworldnow.com">Email Us</a><br />600 Third Ave<br />2 Floor, Suite 242<br />New York, NY 10016<br />646.861.0571</p>
      </div>
    </div>
    <script type="text/javascript">
    jQuery(function($){
      $('.home-wrap .section-wrap .left .left .view-sponsors').scrollable({
        circular: true,
        next: '.home-wrap .section-wrap .left .left .controls-sponsors .next',
        prev: '.home-wrap .section-wrap .left .left .controls-sponsors .prev'
      }).autoscroll({
        autoplay: true,
        interval: 5000
      });
      $('a.video').click(function(e){
        e.preventDefault();
        var $this = $(this);
        $this.overlay({
          mask: 'black',
          onBeforeLoad: function() {
            var wrap = this.getOverlay().find(".contentWrap");
            wrap.load(this.getTrigger().attr("href"));
          },
          load: true,
          effect: 'apple'
        });
      });
    });
    </script>
<?php include 'page/footer-hp.tpl.php'; ?>