<?php /* 1.4 */ ?>

<style>
#loadImg{position:absolute;z-index:999;text-align: center;left: 480px;}
#loadImg div{display:table-cell;width:100%;height:20px;top: 20px;text-align:center;vertical-align:middle;box-sizing: border-box;padding: 40px;}
</style>
<div id="loadImg"><div><img src="/sites/all/themes/cmwn/assets/img/CMW2.gif" style="width: auto;height: 200px;opacity: .5;" /></div></div>
<iframe name="iframe" class="block shadow" height="221px" width="100%" src="http://aiselector.changemyworldnow.com?uid=<?php print $data->user->uid;?>&rand=<?php print rand(1,10000);?>" border="0" scrolling="no" scrollbars="none" frameborder="0" onload="document.getElementById('loadImg').style.display='none';"></iframe>




<?php if(false):?>
<div class="block shadow flips browse index">

	<div class="header">

		<div class="section">
			<h2>Action Items</h2>
		</div>

	</div>

	<div class="content">

		<?php if (($data->user->uid != $user->uid && sizeof($data->items->completed) > 0) || (sizeof($data->items->completed) > 0 || ($data->user->uid == $user->uid && sizeof($data->items->new) > 0))) { ?>
			<div class="section">
				<div<?php print ($data->user->uid == $user->uid && sizeof($data->items->new) > 0)? ' class="column"' : ''; ?>>
					<?php if ($data->user->uid == $user->uid) { ?>
						<div class="title">
							<h3>Your Earned Flips: <em><?php print sizeof($data->items->completed); ?></em> out of <em><?php print sizeof($data->items->all); ?></em></h3>
							<a href="/user/<?php print $user->uid; ?>/flips/browse">View All</a>
						</div>
					<?php } else { ?>
						<div class="title">
							<h3>Earned Flips: <em><?php print sizeof($data->items->completed); ?></em></h3>
						</div>
					<?php } ?>
					<?php if (sizeof($data->items->completed) > 0) { ?>
						<div class="items">
							<?php foreach ($data->items->completed as $item) { ?>
								<div class="item">
									<?php if ($data->user->uid == $user->uid) { ?><a href="<?php print $item->href; ?>"><?php } ?>
										<span class="n1"><img src="<?php print $item->src1; ?>" alt="<?php print $item->title; ?>" /></span>
										<span class="n2" style="height:<?php print $item->progress; ?>%;"><img src="<?php print $item->src2; ?>" alt="<?php print $item->title; ?>" /></span>
									<?php if ($data->user->uid == $user->uid) { ?></a><?php } ?>
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
				<?php if ($data->user->uid == $user->uid && sizeof($data->items->new) > 0) { ?>
					<div class="column">
						<div class="title">
							<h3>Start a New Project</h3>
							<a href="/user/<?php print $user->uid; ?>/flips/browse">View All</a>
						</div>
						<div class="items">
							<?php foreach ($data->items->new as $item) { ?>
								<div class="item">
									<?php if ($data->user->uid == $user->uid) { ?><a href="<?php print $item->href; ?>"><?php } ?>
										<span class="n1"><img src="<?php print $item->src1; ?>" alt="<?php print $item->title; ?>" /></span>
										<span class="n2" style="height:<?php print $item->progress; ?>%;"><img src="<?php print $item->src2; ?>" alt="<?php print $item->title; ?>" /></span>
									<?php if ($data->user->uid == $user->uid) { ?></a><?php } ?>
									<?php render_description($item); ?>
								</div>
							<?php } ?>
						</div>
					</div>
				<?php } ?>
			</div>
		<?php } ?>

		<?php if (sizeof($data->items->started) > 0) { ?>
			<div class="section">
				<?php if ($data->user->uid == $user->uid) { ?>
					<div class="title">
						<h3>Your In-Progress Action Items: <em><?php print sizeof($data->items->started); ?></em></h3>
						<a href="/user/<?php print $user->uid; ?>/flips/browse">Find More Action Items</a>
					</div>
				<?php } else { ?>
					<div class="title">
						<h3>In-Progress Action Items: <em><?php print sizeof($data->items->started); ?></em></h3>
					</div>
				<?php } ?>
				<div class="items">
					<?php foreach ($data->items->started as $item) { ?>
						<div class="item">
							<?php if ($data->user->uid == $user->uid) { ?><a href="<?php print $item->href; ?>"><?php } ?>
								<span class="n1"><img src="<?php print $item->src1; ?>" alt="<?php print $item->title; ?>" /></span>
								<span class="n2" style="height:<?php print $item->progress; ?>%;"><img src="<?php print $item->src2; ?>" alt="<?php print $item->title; ?>" /></span>
							<?php if ($data->user->uid == $user->uid) { ?></a><?php } ?>
							<?php render_description($item); ?>
						</div>
					<?php } ?>
				</div>
			</div>
		<?php } ?>

	</div>

</div>
<?php endif;?>