<?php /*    <div class="bottom-content">
      <?php print $bottom_content; ?>
    </div>
    <div class="footer">
      <div class="inner-wrap">
        <div class="credits"><a href="http://www.r2integrated.com/" rel="external">Site Developed by</a></div>
        <?php print $footer; ?>
        <div class="footer_links">
        <?php print $footer_links; ?>
        </div>
        <div class="footer_utilities">
        <?php print $footer_utilities; ?>
        </div>
        <div class="copyright"></div>
      </div>
    </div>*/ ?>
    <div class="bottom-content">

      <div style="float:left;width:206px;margin:40px 0 20px 60px;">
        <img src="<?php print $theme_path; ?>/assets/img/new-hp/partners.png" />
        <div style="position:relative;">
        <?php echo views_embed_view('sponsors', 'default'); ?>
        </div>
        <img style="float:left;margin:0 0 20px 0;" src="<?php print $theme_path; ?>/assets/img/new-hp/contact-us.png" />
          <p style="margin:0 0 20px 0;float:left;"><a style="font-weight:bold;color:#848077;" href="mailto:info@changemyworldnow.com">Email Us</a><br />600 Third Ave<br />2 Floor, Suite 242<br />New York, NY 10016<br />646.861.0571 </p>
        <img style="float:left;margin-right:16px" src="<?php print $theme_path; ?>/assets/img/new-hp/follow-us.png" />
       <?php if(false):?>
        <div class="social">
          <a href="http://www.facebook.com/ChangeMyWorldNow" class="facebook" title="Friend us on Facebook">Facebook</a>
          <a href="http://twitter.com/CMyWorldNow" class="twitter" title="Follow us on Twitter">Twitter</a>
        </div>
        <?php endif;?>
      </div>
      <div class="footer_utilities">
      <?php //print $footer_utilities; ?>
      </div>
    </div>
    <div class="footer">
    </div>
  </div>
  <div id="overlay-video"><div class="contentWrap"></div></div>
  <?php print $overlay; ?>
  <?php print $closure; ?>
</body>
</html>