<?php include 'page/header.tpl.php'; ?>
    <div class="section-wrap">
        <div class="pad-wrap">
        <div class="int-nav">
          <?php print $int_nav; ?>
        </div>
        <?php print $messages; ?>
        <?php print $help; ?>
        <?php print $content_top; ?>
        <script type="text/javascript">
        jQuery(function($){
          $('.views-field-field-viddler-thumbnail-value a').live('click', function(e){
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
        <script type="text/javascript">
        jQuery(function($){
          var $interests = $('.whats-my-story-my-interests .interest');
          $interests.each(function(){
            var $interest = $(this);
            var $classes = $($interest.attr('class').split(' '));
            $classes.each(function(){
              if (this.indexOf('interest-') === 0) {
                var nid = this.substr(9);
                $interest.find('a').click(function(e){
                  var $a = $(this);
                  if ($a.parents('.interest').hasClass('selected')) {
                    return true;
                  }
                  $interests.removeClass('selected');
                  $a.parents('.interest').addClass('selected');
                  e.preventDefault();
                  $.ajax({
                    url: '/whats-my-story/my-interests/ajax/'+parseInt(nid),
                    success: function(data) {
                      $('.brand-partner-videos').html(data);
                      $('a.brand-partner-videos-view-all').show().attr('href', $a.attr('href'));
                    }
                  });
                });
              }
            });
          });
        });
        </script>
        <div class="whats-my-story-my-interests">
        <?php print $content; ?>
        </div>
        <img src="<?php echo url(drupal_get_path('theme', 'cmwn')); ?>/assets/img/my-interests.png" style="margin:0 0 -20px;" />
        <?php include 'rounded/rounded-top-cutoff.tpl.php'; ?>
        <div class="brand-partner-videos">
        
        </div>
        <a class="arrow-link brand-partner-videos-view-all">View All</a>
        <?php include 'rounded/rounded-bottom.tpl.php'; ?>
        <?php print $content_bottom; ?>
        <div class="aside">
          <?php print $sidebar; ?>
        </div>
      </div>
    </div>
<?php include 'page/footer.tpl.php'; ?>