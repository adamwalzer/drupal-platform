
<?php include 'page/header.tpl.php'; ?>
  </div>
  <?php if ($messages) : ?>
  <div class="skin-wrap">
    <div class="section-wrap section-messages">
      <?php print $messages; ?>
    </div>
  </div>
  <?php endif; ?>
  <div class="campaign-wrap">
    <div class="campaign">
    <?php echo $campaign; ?>
    </div>
    <div class="controls-homepage-slideshow">
      <a class="prev browse left"></a>
      <a class="next browse right"></a>
      <div class="navigation">
        <a href="/cool-videos" class="listen">Listen</a>
        <a href="/user" class="talk">Talk</a>
        <a href="/whats-my-story/my-interests" class="shine">Shine</a>
      </div>
    </div>
  </div>
  <div class="skin-wrap <?php print $skin_class; ?>">
    <div class="section-wrap">
      <div class="int-nav">
        <?php print $int_nav; ?>
      </div>
      <div class="section rounded">
        <div class="content">
          <div class="t"></div>
          <div class="wrapper">
            <div class="wrap-left">
              <div class="top left">
                <h2>I Saw the Bus Tour</h2>
                <p>We’re going on the road! Click here to learn more &amp; invite us to your school.</p>
                <a href="/bus-tour"></a>
              </div>
              <div class="top right">
                <h2>Buy Cassandra’s Angel Online</h2>
                <p>The book that has inspired children around the world.</p>
                <a href="http://www.amazon.com/Cassandras-Angel-Gina-Otto/dp/140278743X/ref=sr_1_1?ie=UTF8&qid=1318864765&sr=8-1"></a>
              </div>
              <div class="bottom left">
                <h2>Slumber Party</h2>
                <p>Calling all girls and women... we're planning a big surprise!  Details to come!</p>
                <a href="/events"></a>
              </div>
              <div class="bottom right">
                <h2>For Grown Ups</h2>
                <p>Teachers, Mentors &amp; Parents:  Find great ideas on how to get your kids active!</p>
                <a href="/grown-ups"></a>
              </div>
            </div>
            <div class="wrap-right">
              <div class="panes">
                <div class="pane"><a href="/video/a6addb3f" rel="#overlay-video"><img src="http://cdn-thumbs.viddler.com/thumbnail_2_a6addb3f_v1.jpg" style="width:227px;" /></a></div>
                <div class="pane"><a href="/video/6f33583e" rel="#overlay-video"><img src="http://cdn-thumbs.viddler.com/thumbnail_2_6f33583e_v1.jpg" style="width:227px;" /></a></div>
                <div class="pane"><a href="/video/52b15e13" rel="#overlay-video"><img src="http://cdn-thumbs.viddler.com/thumbnail_2_52b15e13_v1.jpg" style="width:227px;" /></a></div>
              </div>
              <ul class="tabs">
                <li class="one"><a href="#">Casts' Global Wishes</a></li>
                <li class="two"><a href="#">Message from Gina</a></li>
                <li class="three"><a href="#">Cassandra's Angel Video</a></li>
              </ul>
            </div>
          </div>
        </div>
        <div class="b"><div></div></div>
      </div>
      <div class="aside">
        <?php print $sidebar; ?>
      </div>
    </div>
<script type="text/javascript">
jQuery(function($){
  $('.view-homepage-slideshow').scrollable({
    circular: true,
    next: '.controls-homepage-slideshow .next',
    prev: '.controls-homepage-slideshow .prev'
  }).autoscroll({
    autoplay: true,
    interval: 10000
  });
  $('.wrap-right ul.tabs').tabs('.wrap-right div.panes div.pane');
  $('.wrap-right ul.tabs').data('tabs').onClick(function(e){
    centerVideos();
  });
  $('.panes .pane a').click(function(e){
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
  setTimeout(centerVideos, 500);
  function centerVideos() {
    $('.panes .pane img').each(function(){
      $(this).css('margin-top', (184 - $(this).height()) / 2);
    });
  }
});
</script>
<?php include 'page/footer.tpl.php'; ?>