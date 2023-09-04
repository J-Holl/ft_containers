NAME = ft_containers
STDTARGET = std_containers
FT = ft
STD = std
COMPILER  = c++
FT_FLAGS  = -std=c++98 -Wall -Wextra -Werror
STD_FLAGS  = -std=c++98 -Wall -Wextra -Werror -D STD
OBJ = $(SRCS:.cpp=.o)
INC_DIR = inc/
SRC    = main.cpp
FT_OBJECTS=$(SRC:%.cpp=ft/%.o)
STD_OBJECTS=$(SRC:%.cpp=std/%.o)

all: dirs $(NAME)

$(NAME): $(FT_OBJECTS)
	$(COMPILER) $(FT_FLAGS) -I$(INC_DIR) -o $(NAME) $(FT_OBJECTS)

std: dirs $(STDTARGET)

$(STDTARGET): $(STD_OBJECTS)
	$(COMPILER) $(STD_FLAGS) -I$(INC_DIR) -o $(STDTARGET) $(STD_OBJECTS)

ft/%.o: %.cpp $(SRC)
	$(COMPILER) $(FT_FLAGS) -I$(INC_DIR) -c $< -o $@ 

std/%.o:    $(SRC)
	$(COMPILER) $(STD_FLAGS) -I$(INC_DIR) -c $< -o $@ 

dirs:
	@mkdir -p ft std

clean:
	@rm -rf $(FT) $(STD)

fclean: clean 
	@rm -f $(NAME) $(STDTARGET)

re: fclean all

#compare: $(NAME) $(STDTARGET)
#	@./$(NAME) > ft_output_txt 2>&1 
#	@./$(STDTARGET) > std_output_txt 2>&1 
#	diff ft_output_txt std_output_txt

.PHONY:	all clean fclean re make std dirs compare
