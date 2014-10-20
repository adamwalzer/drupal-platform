<?php /* 1.4 */ ?>

<?php include 'page/header.tpl.php'; ?>

<?php

	$_node = node_load(11956);

	$_image = $_node->field_image[0]['filepath'];

	$_video_id = $_node->field_video_reference[0];
	$_video = '';
	$_tmp = node_load($_video_id);
	if ($_tmp) {
		$_video = $_tmp->field_viddler_id[0]['value'];
	}

	$_article_ids = $_node->field_article_references;
	$_articles = array();
	foreach ($_article_ids as $_id)  {
		$_tmp = node_load($_id['nid']);
		if ($_tmp) {
			$_article = new stdClass();
			$_article->nid = $_tmp->nid;
			$_article->link = url('node/'.$_tmp->nid);
			$_article->title = $_tmp->title;
			$_articles[] = $_article;
		}
	}

	$_partner_ids = $_node->field_partner_references;
	$_partners = array();
	foreach ($_partner_ids as $_id)  {
		$_tmp = node_load($_id['nid']);
		if ($_tmp) {
			$_partner = new stdClass();
			$_partner->title = $_tmp->title;
			$_partners[] = $_partner;
		}
	}

?>

<div class="section-wrap">

	<?php print $messages; ?>

	<div id="landing-page">

		<?php if (!empty($_image)) { ?>
			<div class="image">
				<img src="/<?= $_image; ?>" />
			</div>
		<?php } ?>

		<div class="columns">

			<div class="column content">

				<h1><?= $title; ?></h1>

				<?= $content; ?>

				<?php

					//print '<pre>';
					//print_r($_node);
					//print '</pre>';

				?>

			</div>

			<div class="column sidebar">

				<?php if (!empty($_video)) { ?>
					<div class="box shadow video">
						<h4>Featured Video</h4>
						<div class="media">
							<iframe width="318" height="245" src="http://www.youtube.com/embed/Md3mMUTEc0A" frameborder="0" allowfullscreen></iframe>
						</div>
					</div>
				<?php } ?>

				<div class="box shadow articles">
					<h4>Related Articles</h4>
					<div class="items">
						<?php foreach ($_articles as $_article) { ?>
							<div class="item<?= ($_article->nid == $node->nid)? ' active' : ''; ?>">
								<div class="title"><a href="<?= $_article->link; ?>"><?= $_article->title; ?></a></div>
							</div>
						<?php } ?>
					</div>
				</div>

				<div class="box shadow partners">
					<h4>Related Partners</h4>
					<div class="items">
						<?php foreach ($_partners as $_partner) { ?>
							<div class="item">
								<div class="title"><?= $_partner->title; ?></div>
							</div>
						<?php } ?>
					</div>
				</div>

			</div>

		</div>

	</div>

</div>

<?php include 'page/footer.tpl.php'; ?>