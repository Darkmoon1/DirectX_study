#include <conio.h>
#include <stdio.h>
enum CHARACTER_STATE
{
	STATE_LIVE = 0,
	STATE_DEAD
};

enum CHARACTER_ACTION
{
	ACTION_IDLE = 0,
	ACTION_MOVE
};

enum CHARACTER_EVENT
{
	EVENT_EMPTY = 0,
	EVENT_ATTACKED,
	EVENT_RESTART
};

void main()
{
	int _pos = 0;
	int _state = STATE_LIVE;
	int _action = ACTION_IDLE;
	int _event = EVENT_EMPTY;

	int _key;
	while (true)
	{
		_key = _getch();

		if (_key == 'E')
		{
			break;
		}

		_action = ACTION_IDLE;
		if (_key == 'A')
		{
			_action = ACTION_MOVE;
			_pos--;
		}
		if (_key == 'D')
		{
			_action = ACTION_MOVE;
			_pos++;
		}

		switch (_action)
		{
		case ACTION_IDLE:
			//Render idle animation
			//≥ œ÷œ–÷√◊¥Ã¨∂Øª≠
			printf("Idel at position:%d\n", _pos);
			break;
		case ACTION_MOVE:
			//≥ œ÷“∆∂Ø∂Øª≠
			printf("Walk at positon:%d\n", _pos);
			break;
		default:
			break;
		}

		switch (_state)
		{
		case STATE_LIVE:
			switch (_event)
			{
			case EVENT_ATTACKED:
				_state = STATE_DEAD;
				break;
			case EVENT_RESTART:
				//not change the state
				break;
			default:
				break;
			}
			break;
		
		case STATE_DEAD:
			switch (_event)
			{
			case EVENT_ATTACKED:
				break;
			case EVENT_RESTART:
				_state = STATE_LIVE;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}

}