#!/usr/bin/python3
"""
Subreddit keyword counter module
"""

import requests


def count_words(subreddit, word_list, after=None, count_dict=None):
    """
    Recursively counts occurrences of keywords in the titles of hot posts
    from a subreddit.

    Args:
        subreddit (str): Subreddit to search.
        word_list (list): List of keywords to count.
        after (str): 'after' token for pagination (used in recursion).
        count_dict (dict): Dictionary holding keyword counts.

    Returns:
        None. Prints the sorted word counts.
    """
    # Init. count dictionary and convert word_list to lowercase (first call)
    if count_dict is None:
        count_dict = {}
    word_list = [word.lower() for word in word_list]

    # Call the helper function to get posts and the next 'after' token
    posts, after = fetch_reddit_data(subreddit, after)

    # If no valid posts are retrieved, stop here
    if not posts:
        return

    # Count occurrences of words in each post title
    for post in posts:
        title = post['data']['title'].lower().split()

        for word in word_list:
            count_dict[word] = count_dict.get(word, 0) + title.count(word)

    # Base case: if 'after' is None, we have processed all pages
    if after is None:
        # Sort word counts by occurrence (descending), then alphabetically
        sorted_words = sorted(count_dict.items(), key=lambda x: (-x[1], x[0]))

        # Print sorted results
        for word, count in sorted_words:
            if count > 0:
                print(f'{word}: {count}')
        return

    # Recursion: fetch next page of posts, using the updated 'after' token
    return count_words(subreddit, word_list, after, count_dict)


def fetch_reddit_data(subreddit, after=None):
    """
    Fetch hot posts from a subreddit.

    Args:
        subreddit (str): The subreddit to fetch hot posts from.
        after (str): The 'after' token for pagination.

    Returns:
        tuple: A tuple containing the list of posts and the 'after' token
        for the next page.
    """
    # Define the base URL and headers for the Reddit API
    url = f'https://www.reddit.com/r/{subreddit}/hot/.json'
    headers = {'User-Agent': 'KeywordCounter/0.1'}
    params = {'limit': 100, 'after': after}

    # Make the request to the Reddit API
    response = requests.get(url, headers=headers, params=params)

    # If the request fails (or the subreddit is invalid), return None
    if response.status_code != 200:
        return None, None

    # Parse the JSON response and extract posts and the 'after' token
    data = response.json().get('data', {})
    posts = data.get('children', [])
    after = data.get('after')

    return posts, after
