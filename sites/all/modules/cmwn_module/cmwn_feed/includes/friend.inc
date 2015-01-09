<?php
  
global $cmwn_feed_menu_items;
$cmwn_feed_menu_items['cmwn_feed/friend'] = array(
  'page callback' => 'cmwn_friend_feed',
  'access arguments' => array('access content'),
  'type' => MENU_CALLBACK,
);
  
function cmwn_feed_friend_queries_list(){
  $feed_queries = array(
    'friend request',
    'completes flip milestone',
    'signs up flip',
    'completes flip',
    'post on own whiteboard',
    'post on other whiteboard', 
    'joins special edition flip', 
    'reply to own post', 
    'reply to other post', 
  );  
  return $feed_queries;
}

function cmwn_feed_friend_query_weights(){
  
  $friend_feed_queries = cmwn_feed_friend_queries_list();
  
  $friend_feed_weights = db_placeholders(cmwn_feed_friend_queries_list($friend_feed_queries));
  
  $result = db_query("SELECT query_name, weight FROM {cmwn_feed_weight} cfw where query_name in ($friend_feed_weights)", $friend_feed_queries);
  
  $weights = array();
  
  while ($row = db_fetch_object($result)) {
    $weights[$row->query_name] = (float)$row->weight;
  }     
  
  return $weights;

}

function cmwn_feed_get_timeago($field){
  return "CASE 
            WHEN FROM_UNIXTIME(" . $field . ") between date_sub(now(), INTERVAL 60 minute) and now() THEN concat(minute(TIMEDIFF(now(), FROM_UNIXTIME(" . $field . "))), ' minute(s) ago')
            WHEN datediff(now(), FROM_UNIXTIME(" . $field . ")) = 1 THEN 'Yesterday'
            WHEN FROM_UNIXTIME(" . $field . ") between date_sub(now(), INTERVAL 48 hour) and now() THEN concat(hour(TIMEDIFF(NOW(), FROM_UNIXTIME(" . $field . "))), ' hour(s) ago')
          ELSE date_format(FROM_UNIXTIME(" . $field . "), '%a, %m/%%d/%y %h:%%i%p')
          END      	as time_ago
          ";
}  

function cmwn_friend_feed($uid = 0, $page = 0) {
    
		$items = array();
    global $user;
    global $feed_queries;
    $weights = cmwn_feed_friend_query_weights();
		$friend_feed_user = user_load($uid);

		if (!$friend_feed_user || $user->uid != $uid){
  		print '';
  		exit();
		} 		

		//Friend feed - find all this person's friends first!
		$query = "SELECT requester_id as friend_uid FROM {user_relationships} WHERE requestee_id = %d and approved =1 order by updated_at desc";
		
		$results = db_query($query, $uid);

    $friends = array();
    
		while ($result = db_fetch_object($results)) {
      $friends[] = $result->friend_uid;
		}
		
		//add our uid!
		$friends[] = $uid;
    
    $friend_uid_placeholders = db_placeholders($friends);
		
    $feed_queries['friend request'] = "(SELECT 
        CONCAT('<a href=\"/user/', user_a.uid,'\">',user_a.name,'</a> has become friends with <a href=\"/user/',user_b.uid, '\">', user_b.name, '</a>') as excerpt, 
        user_a.uid as uid, 
        updated_at as stamp, 
        (updated_at*".$weights['friend request'].") as s,
        ".cmwn_feed_get_timeago('updated_at')."
      	
        FROM {user_relationships} ur 
        JOIN {users} user_a ON ur.requester_id = user_a.uid 
        JOIN {users} user_b ON user_b.uid = ur.requestee_id 
        WHERE requester_id in($friend_uid_placeholders) and approved = 1)";
      
    $feed_queries['completes flip milestone'] = "(SELECT 
        CONCAT('<a href=\"/user/', u.uid,'\">',u.name,'</a> has completed the action item milestone \"<em>', n.title ,'</em>.\"') as excerpt, 
        ws.uid as uid, 
        submitted as stamp, 
        (submitted*".$weights['completes flip milestone'].") as s,
        ".cmwn_feed_get_timeago('submitted')."
        
        FROM {webform_submissions} ws 
        JOIN {node} n ON n.nid = ws.nid 
        JOIN {users} u ON u.uid = ws.uid AND n.type='action' 
        WHERE ws.uid in($friend_uid_placeholders)) ";
      
      $feed_queries['signs up flip'] = "(select 
        CONCAT('<a href=\"/user/', u.uid,'\">',u.name,'</a> has begun the action item \"<em>', nf.title ,'</em>.\"') as excerpt, 
        ws.uid as uid, 
        ws.submitted as stamp, 
        (ws.submitted*".$weights['signs up flip'].") as s,
        ".cmwn_feed_get_timeago('ws.submitted')."
          
        FROM {webform_submissions} ws 
        JOIN node na ON ws.nid = na.nid 
        JOIN {content_field_actions} cfa ON cfa.field_actions_nid = na.nid 
        JOIN {node} nf ON nf.nid = cfa.nid 
        JOIN {users} u ON u.uid = ws.uid 
        WHERE ws.uid in($friend_uid_placeholders) AND cfa.delta = (select min(delta) FROM {content_field_actions} cfai where cfai.nid = nf.nid)) ";

      $feed_queries['joins special edition flip'] = "(select 
        CONCAT('<a href=\"/user/', u.uid,'\">',u.name,'</a> has begun has joined special edition flip \"<em>', nf.title ,'</em>.\"') as excerpt, 
        ws.uid as uid, 
        ws.submitted as stamp, 
        (ws.submitted*".$weights['joins special edition flip'].") as s,
        ".cmwn_feed_get_timeago('ws.submitted')."

        FROM {webform_submissions} ws 
        JOIN node na ON ws.nid = na.nid 
        JOIN {content_field_actions} cfa ON cfa.field_actions_nid = na.nid 
        JOIN {node} nf ON nf.nid = cfa.nid 
        JOIN {users} u ON u.uid = ws.uid 
        JOIN {content_field_special_edition} cfse ON cfse.nid = nf.nid AND cfse.field_special_edition_value='Yes' 
        WHERE ws.uid in($friend_uid_placeholders) AND cfa.delta = (select min(delta) FROM {content_field_actions} cfai WHERE cfai.nid = nf.nid)) ";

      
      $feed_queries['completes flip'] = "(select 
        CONCAT('<a href=\"/user/', u.uid,'\">',u.name,'</a> has completed the action item \"<em>', nf.title ,'</em>.\"') as excerpt, 
        ws.uid as uid, ws.submitted as stamp, 
        (ws.submitted*".$weights['completes flip'].") as s,
        ".cmwn_feed_get_timeago('ws.submitted')."
        
        FROM {webform_submissions} ws JOIN node na ON ws.nid = na.nid 
        JOIN {content_field_actions} cfa ON cfa.field_actions_nid = na.nid 
        JOIN {node} nf ON nf.nid = cfa.nid 
        JOIN {users} u ON ws.uid = u.uid 
        WHERE ws.uid in($friend_uid_placeholders) AND cfa.delta = (select max(delta) FROM {content_field_actions} cfai WHERE cfai.nid = nf.nid)) ";
      $feed_queries['reply to own post'] = "(select CONCAT('<a href=\"/user/', c.uid,'\">', u.name, '</a> has commented on their own post.<br />\"' , (case 
      	when length(c.comment) > 25 
        then concat(substring(c.comment, 1, 25), '...')
        else c.comment
         end) , '\"') as excerpt, 
      	c.uid as uid,
      	  timestamp as stamp, 
      	  (timestamp*".$weights['reply to own post'].") as s,
      	
        ".cmwn_feed_get_timeago('timestamp')."

        FROM {comments} c 
        JOIN {node} n ON n.type = 'whiteboard' AND n.nid = c.nid 
        JOIN {content_type_whiteboard} ctw ON ctw.nid = n.nid AND ctw.field_user_reference_uid = c.uid
        JOIN {users} u ON u.uid = c.uid
        WHERE c.uid IN ($friend_uid_placeholders) and c.status = 0)";      
      
      $feed_queries['reply to other post'] = "(select CONCAT('<a href=\"/user/', c.uid,'\">', u.name, '</a> has commented on <a href=\"/user/', u2.uid,'\">' , u2.name , '\\'s</a> post.<br />\"' , (case 
      	when length(c.comment) > 25 
        then concat(substring(c.comment, 1, 25), '...')
        else c.comment
         end) , '\"') as excerpt, 
      	c.uid as uid,
      	  timestamp as stamp, 
      	  (timestamp*".$weights['reply to other post'].") as s,
      	
        ".cmwn_feed_get_timeago('timestamp')."

        FROM {comments} c 
        JOIN {node} n ON n.type = 'whiteboard' AND n.nid = c.nid 
        JOIN {content_type_whiteboard} ctw ON ctw.nid = n.nid AND ctw.field_user_reference_uid <> c.uid
        JOIN {users} u on u.uid = c.uid
        JOIN {users} u2 on u2.uid = n.uid
        WHERE c.uid IN ($friend_uid_placeholders) AND c.status =0)";
      
      //carefully note - the field_user_reference on this websites determines who actually made the post. node.uid is not the actual author but whose whiteboard the post appears on.
      $feed_queries['post on own whiteboard'] = "(select CONCAT('<a href=\"/user/', n.uid,'\">', u.name, '</a> has posted on their own whiteboard.') as excerpt, 
      	n.uid as uid,
        n.created as stamp, 
      	(n.created*".$weights['post on own whiteboard'].") as s,
      	".cmwn_feed_get_timeago('n.created')."

        FROM {node} n 
        JOIN {users} u ON u.uid = n.uid 
        JOIN {content_type_whiteboard} ctw ON ctw.nid = n.nid AND ctw.field_user_reference_uid = n.uid 
        WHERE n.type='whiteboard' AND ctw.field_user_reference_uid in ($friend_uid_placeholders) AND n.status = 1)";


      $feed_queries['post on other whiteboard'] = "(select CONCAT('<a href=\"/user/', u2.uid, '\">', u2.name, '</a> has posted on <a href=\"/user/', u.uid,'\">', u.name ,'s</a> whiteboard.') as excerpt, 
      	n.uid as uid,
        n.created as stamp, 
      	(n.created*".$weights['post on other whiteboard'].") as s,
      	".cmwn_feed_get_timeago('n.created')."

        FROM {node} n JOIN {users} u ON u.uid = n.uid 
        JOIN {content_type_whiteboard} ctw ON ctw.nid = n.nid 
        JOIN {users} u2 ON u2.uid = ctw.field_user_reference_uid 
        WHERE ctw.field_user_reference_uid <> n.uid AND n.type='whiteboard' AND n.status = 1 AND ctw.field_user_reference_uid IN ($friend_uid_placeholders))";
      
    
		$args = array();
    foreach($feed_queries as $type => $query){
      $args = array_merge($args,$friends);
    }

    $query_union = implode(' UNION ALL ', $feed_queries) . '  order by s desc';

    $count_query = "SELECT COUNT(*) FROM (" . $query_union . ") AS count_query";
    

    
    $feed_items = pager_query($query_union, 13, 0, $count_query, $args);//careful here, $args must work for count query and main query or this wont work.

    while($f = db_fetch_object($feed_items)){
      $item = new stdClass();
  		$item->excerpt = $f->excerpt;
      $item->src = v2_profiles_avatars_query($f->uid);
  		$item->stamp = $f->stamp;
  		$item->time_ago = $f->time_ago;
  		$items[] = $item;
    }
		?>
		
    <?php foreach ($items as $item) { ?>
      	<div class="item">
      		<span class="image">
      			<img height="42" src="<?php print $item->src; ?>" width="42" />
      		</span>
      		<?php
      			$_excerpt = $item->excerpt  . ' <em class="feed-time">' .  $item->time_ago . '</em>';
      			$_excerpt = str_replace('/user/'.$user->uid, '/user', $_excerpt);
      			$_excerpt = preg_replace('/("\/user\/)([0-9]+)(")/i', '"/user/'.$user->uid.'/friends/$2/"', $_excerpt);
      		?>
      		<span class="message">
      			<?php print $_excerpt; ?>
      		</span>
      	</div>
    <?php } ?>		
    <?php
      print theme('pager', NULL, 10, 0);
      exit;
}