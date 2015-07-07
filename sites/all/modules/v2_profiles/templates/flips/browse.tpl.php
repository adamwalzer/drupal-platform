<?php  switch(true):?>
<?php case true:?>
<iframe class="block shadow" src="http://demoai.changemyworldnow.com?uid=<?php print $data->uid?>&BrowseType=Child" width="100%" height="735px" frameborder="no" scrollbars
	="none" scrolling="no"></iframe>

<?php break;?>


<?php case false:?>


<?php /* 1.4 */ ?>

<div class="block shadow flips browse">

	<div class="header">

		<div class="section">
			<h2>Action Items</h2>
		</div>

		<div class="section form">
			<form action="/user/<?php print $data->user->uid; ?>/flips/search" method="post">
				<?php /*
					<input name="q" placeholder="Search Flips" type="text" />
					<button class="button" type="submit">Go!</button>
				*/ ?>
				<a class="button filter" href="#">Sort By Interest</a>
			</form>
		</div>

	</div>

	<div class="content">

		<div class="section">
			<?php if (sizeof($data->items) > 0) { ?>
				<div class="items">
					<?php foreach ($data->items as $item) { ?>
						<div class="<?php print $item->class; ?>">
							<a href="<?php print $item->href; ?>">
								<span class="n1"><img src="<?php print $item->src1; ?>" alt="<?php print $item->title; ?>" /></span>
								<span class="n2" style="height:<?php print $item->progress; ?>%;"><img src="<?php print $item->src2; ?>" alt="<?php print $item->title; ?>" /></span>
							</a>
							<?php render_description($item); ?>
						</div>
					<?php } ?>
				</div>
			<?php } else { ?>
				<div class="empty">
					There are no action items.
				</div>
			<?php } ?>
		</div>

	</div>

</div>

<div class="block flips modal interests" id="flips-interests" style="display:none;">

	<div class="section">
		<ul>
			<?php foreach ($data->interests as $item) { ?>
				<li class="<?php print $item->class; ?>"><a href="<?php print $item->href; ?>" data-filter=".tid-<?php print $item->id; ?>"><?php print $item->title; ?></a></li>
			<?php } ?>
		</ul>
	</div>

</div>
<?php break;?>

<?php endswitch;?>
