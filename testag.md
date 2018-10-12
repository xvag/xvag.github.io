---
layout: page
title: testag 
permalink: /testag/
---

<div class="home">
	<section class="site-header">
		<h1 class="smallcap"><a class="site-title" href="{{ site.baseurl }}/">{{ site.title }}</a></h1>
		{% include nav.html %}
	</section>
	<section>
		<ul class="post-list">
			{% for linux in site.tags %}
			<li>
				<a href="{{ post.url | prepend: site.baseurl }}">{{ post.title }}</a>
			</li>
			{% endfor %}
		</ul>
	</section>
</div>
