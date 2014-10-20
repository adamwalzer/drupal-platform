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
      <div style="float:left;margin:40px 60px 40px 60px;">
        <img src="<?php print $theme_path; ?>/assets/img/new-hp/extras.png" />
        <ul class="menu">
          <li><a href="/ginas-corner/our-vision">Our Vision</a></li>
          <li><a href="/ginas-corner/ginas-ink">Gina's Ink</a></li>
          <li><a href="/node/2561">Letter to Parents</a></li>
          <li><a href="/events">Where in the World is Gina?</a></li>
        </ul>
      </div>
      <div style="float:left;width:200px;margin:20px 60px 20px 60px">
        <a style="float:left;margin:6px 0 0 0;" href="/bus-tour"><img src="<?php print $theme_path; ?>/assets/img/new-hp/saw-bustour.png" /></a>
        <div style="float:left;margin:20px 0 0 0;width:200px;">
          <img src="<?php print $theme_path; ?>/assets/img/new-hp/cassandras-angel.png" />
          <p style="margin:10px 0 0 0">Cassandra’s Angel is about the negative stories that Cassandra – and all of us – are told our entire lives. It’s about who people think we are. Luckily, Cassandra discovers that she is not alone. Come follow Cassandra on a journey that just might change your life.</p>
          <p style="margin:0 0 20px 0"><a style="font-weight:bold;color:#848077;" href="http://www.barnesandnoble.com/w/cassandras-angel-gina-otto/1100276059">Purchase the Book</a></p>
        </div>
      </div>
      <div style="float:left;width:206px;margin:40px 0 20px 60px;">
        <img src="<?php print $theme_path; ?>/assets/img/new-hp/partners.png" />
        <div style="position:relative;">
        <?php echo views_embed_view('sponsors', 'default'); ?>
        </div>
        <img style="float:left;margin:0 0 20px 0;" src="<?php print $theme_path; ?>/assets/img/new-hp/contact-us.png" />
        <p style="margin:0 0 20px 0;float:left;"><a style="font-weight:bold;color:#848077;" href="mailto:info@changemyworldnow.com">Email Us</a><br />32 Union Sq. East<br />New York, NY. 10003</p>
        <img style="float:left;margin-right:16px" src="<?php print $theme_path; ?>/assets/img/new-hp/follow-us.png" />
        <div class="social">
          <a href="http://www.facebook.com/ChangeMyWorldNow" class="facebook" title="Friend us on Facebook">Facebook</a>
          <a href="http://twitter.com/CMyWorldNow" class="twitter" title="Follow us on Twitter">Twitter</a>
        </div>
      </div>
      <div class="footer_utilities">
      <?php print $footer_utilities; ?>
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