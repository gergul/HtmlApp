$(document).ready(function() {
    var colour_array = ['blue', 'orange', 'red', 'green', 'darkgreen', 'purple', 'darkred', 'darkblue', 'yellow', 'grey'];

    var header_html = '';
    header_html += '<div id="settings"></div>';
    header_html += '<div id="theme_picker">';
    header_html +=     '<span>Theme:</span>';
    header_html +=     '<div class="selected">';
    header_html +=         '<div class="square default"></div>';
    header_html +=         '<label class="text_shadow">custom</label>';
    header_html +=      '</div>';

    $(colour_array).each(function(index, colour) {
        header_html += '<div>';
        header_html +=     '<div class="square ' + colour + '"></div>';
        header_html +=     '<label class="text_shadow">' + colour + '</label>';
        header_html += '</div>';
    });

    header_html += '</div>';

    $('<header>').html(header_html).prependTo($(document.body));

    var settingClick = function() {
        $(document.body).toggleClass('open');
    };

    var themeClick = function(e) {
        var theme = $(this).children('div.square').attr('class');

        $.each(colour_array, function(index, value) {
            $('div.widget_container').removeClass(value);
        });

        if (theme !== 'default') {
            $('div.widget_container').addClass(theme);
        }

        $('#theme_picker').children('div.selected').removeClass('selected');
        $(this).addClass('selected');
    };

    $('#theme_picker').children('div').click(themeClick)
    $('#settings').click(settingClick);
});