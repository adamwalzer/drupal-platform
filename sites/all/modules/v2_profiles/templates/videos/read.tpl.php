<?php /* 1.4 */ ?>

<!DOCTYPE html>
<html>

	<head>

		<link href="/sites/all/themes/cmwn/assets/css/all.css" media="all" rel="stylesheet" type="text/css" />

	</head>

	<body>

		<div id="v2">

			<div class="block simplemodal">

				<div class="header">

					<div class="section">
						<h2>Now Playing</h2>
					</div>

					<div class="section buttons">
						<a class="close" href="#" onclick="parent.$.modal.close();">Close</a>
					</div>

				</div>

				<div class="content">

					<div class="section details">
						<div class="name">
							<?php print $data->item->title; ?>
						</div>
						<div class="user">
							By
							<?php $_user = user_load($data->item->uid); ?>
							<?php print $_user->name; ?>
						</div>
						<div class="date">
							<?php print date('m/d/Y',$data->item->created); ?>
						</div>
					</div>

					<div class="section media">
						<object
							classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000"
							height="417"
							width="741"
						>
							<param name="movie" value="//www.viddler.com/mini/<?php print $data->item->field_viddler_id[0]['value']; ?>/"/>
							<param name="allowScriptAccess" value="always"/>
							<param name="allowNetworking" value="all"/>
							<param name="allowFullScreen"value="true"/>
							<param name="flashVars" value="f=1&amp;autoplay=t&amp;loop=0&amp;nologo=1&amp;hd=1"/>
							<embed
								allowFullScreen="true"
								allowNetworking="all"
								allowScriptAccess="always"
								flashVars="f=1&amp;autoplay=t&amp;loop=0&amp;nologo=1&amp;hd=1"
								height="417"
								src="//www.viddler.com/mini/<?php print $data->item->field_viddler_id[0]['value']; ?>/"
								type="application/x-shockwave-flash"
								width="741"
							></embed>
						</object>
					</div>

				</div>

			</div>

		</div>

	</body>

</html>