<?php

	$allow_registrations = true;
	if ($_GET['allow_registrations'] === 'true') {
		setcookie('allow_registrations', 'true', strtotime('+1 year'));
		header('Location: http://' . $_SERVER['SERVER_NAME']);
	}
	if ($_SERVER['SERVER_NAME'] === 'ginasinkstg.prod.acquia-sites.com' && !isset($_COOKIE['allow_registrations'])) {
		$allow_registrations = false;
	}
  $allow_registrations = true;

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>">

<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
  <?php print $styles; ?>
  <?php print $scripts; ?>
  
  <link rel="stylesheet" type="text/css" href="//cdn.jsdelivr.net/jquery.slick/1.5.7/slick.css"/>
  <script type="text/javascript" src="//cdn.jsdelivr.net/jquery.slick/1.5.7/slick.min.js"></script>

</head>
<body>
  <div class="skin-wrap <?php print $skin_class; ?>">
    <div class="header">
      <div class="outer-wrap">
        <div class="inner-wrap">
          <div class="logo"><a href="/"></a></div>
          <div class="top-tabs">
            <?php if(false):?>
            <div class="graphic-tab-wrapper">
              <?php if ($user->uid == 0) : ?>
                <?php if ($allow_registrations) : ?>
                  <a class="join-now" href="/register-choose"><img rel="rollover" src="<?php print $theme_path; ?>/assets/img/new-hp/join-now_off.png" /></a>
                  <a class="login" href="/user">Login</a>
                <?php endif; ?>
    			   <?php endif; ?>
            </div>
          <?php endif;?>

          <?php if(false):?>
            <div class="right-nav-wrap">
              <div class="utility-nav">
                <?php print $secondary_links; ?>
              </div>
              <?php echo theme('cmwn_module_social'); ?>
            </div>
          <?php endif; ?>

          <?php if ($user->uid == 0) : ?>
            <a class="pt" href="/node/11"><img rel="rollover" src="<?php print $theme_path; ?>/assets/img/new-hp/pt_off.png" /></a>
          <?php else : ?>
            <?php if (arg(0) == 'user') { ?>
              <a class="pt" href="/logout"><img rel="rollover" src="<?php print $theme_path; ?>/assets/img/new-hp/pt_logout_off.png" /></a>
            <?php } else { ?>
              <a class="pt" href="/user"><img rel="rollover" src="<?php print $theme_path; ?>/assets/img/new-hp/pt_profile_off.png" /></a>
            <?php } ?>
          <?php endif; ?>




          </div>


          <div class="main-nav">
            <?php print $primary_links; ?>
          </div>
        </div>
      </div>
    </div>
