#define CATCH_CONFIG_MAIN

#include <iostream>
#include "catch.hpp"
#include "../datastructures/Environment.h"
#include "../random/Random.h"
#include "../datastructures/LA.h"
#include "../datastructures/State.h"
#include "../algorithms/MCLearning.h"
#include "../algorithms/QLearning.h"

//Todo: Saving en Loading Test (Lars),

TEST_CASE("Environment Basics") {
    Environment env = Environment(10, 5, 42, true, -0.01, 10, 0.2);
    REQUIRE(env.height == 10);
    REQUIRE(env.width == 5);
    REQUIRE(env.start != env.end);
    REQUIRE(env.states.size() == 50);
}

TEST_CASE("Environment Generation: Deterministic without Obstacles") {
    Environment env = Environment(10, 5, 42, true, -0.01, 10, 0.0);
    SECTION("edge state (0, 0), action: left") {
        MDPState *edge_state = env.get_state_by_coordinates(0, 0);
        std::tuple<MDPState *, float> edge_state_reward(edge_state, env.living_reward);
        // go to the left
        int action = 3;
        std::map<std::tuple<MDPState *, float>, float> state_reward_prob = env.p(edge_state, action);
        // can only be one next state since it's a deterministic environment
        REQUIRE(state_reward_prob.size() == 1);
        // the next state should be the current state
        REQUIRE(state_reward_prob.begin()->first == edge_state_reward);
        // probability should be 100% (deterministic)
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }

    SECTION("edge state (0, 0), action: up") {
        MDPState *edge_state = env.get_state_by_coordinates(0, 0);
        std::tuple<MDPState *, float> edge_state_reward(edge_state, env.living_reward);
        // go up
        int action = 0;
        std::map<std::tuple<MDPState *, float>, float> state_reward_prob = env.p(edge_state, action);
        // can only be one next state since it's a deterministic environment
        REQUIRE(state_reward_prob.size() == 1);
        // next state should be (0, 1) when going up
        MDPState *next_state = env.get_state_by_coordinates(0, 1);
        std::tuple<MDPState *, float> next_state_reward(next_state, env.living_reward);
        REQUIRE(state_reward_prob.begin()->first == next_state_reward);
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }

    SECTION("edge state (4, 9), action: up") {
        MDPState *edge_state = env.get_state_by_coordinates(4, 9);
        std::tuple<MDPState *, float> edge_state_reward(edge_state, env.living_reward);
        // go up
        int action = 0;
        std::map<std::tuple<MDPState *, float>, float> state_reward_prob = env.p(edge_state, action);
        // can only be one next state since it's a deterministic environment
        REQUIRE(state_reward_prob.size() == 1);
        // the next state should be the current state
        REQUIRE(state_reward_prob.begin()->first == edge_state_reward);
        // probability should be 100% (deterministic)
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }


    SECTION("edge state (4, 9), action: down") {
        MDPState *edge_state = env.get_state_by_coordinates(4, 9);
        std::tuple<MDPState *, float> edge_state_reward(edge_state, env.living_reward);
        // go up
        int action = 2;
        std::map<std::tuple<MDPState *, float>, float> state_reward_prob = env.p(edge_state, action);
        // can only be one next state since it's a deterministic environment
        REQUIRE(state_reward_prob.size() == 1);
        // next state should be (0, 1) when going up
        MDPState *next_state = env.get_state_by_coordinates(4, 8);
        std::tuple<MDPState *, float> next_state_reward(next_state, env.living_reward);
        REQUIRE(state_reward_prob.begin()->first == next_state_reward);
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }

    SECTION("edge state (4, 9), action: right") {
        MDPState *edge_state = env.get_state_by_coordinates(4, 9);
        std::tuple<MDPState *, float> edge_state_reward(edge_state, env.living_reward);
        // go up
        int action = 1;
        std::map<std::tuple<MDPState *, float>, float> state_reward_prob = env.p(edge_state, action);
        // can only be one next state since it's a deterministic environment
        REQUIRE(state_reward_prob.size() == 1);
        // the next state should be the current state
        REQUIRE(state_reward_prob.begin()->first == edge_state_reward);
        // probability should be 100% (deterministic)
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }
}

TEST_CASE("Environment Generation: Deterministic with Obstacles") {
    Environment env = Environment(5, 2, 87, true, -0.01, 10, 0.2);

    // this seed and configuration leads to (1, 0) and (0, 1) being chosen as obstacles
    // todo this result will change when we implement the path checking!
    SECTION("edge state (0, 0), action: up") {
        MDPState *edge_state = env.get_state_by_coordinates(0, 0);
        std::tuple<MDPState *, float> edge_state_reward(edge_state, env.living_reward);
        // go up
        int action = 0;
        std::map<std::tuple<MDPState *, float>, float> state_reward_prob = env.p(edge_state, action);
        REQUIRE(state_reward_prob.size() == 1);
        REQUIRE(state_reward_prob.begin()->first == edge_state_reward);
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }

    SECTION("edge state (0, 0), action: right") {
        MDPState *edge_state = env.get_state_by_coordinates(0, 0);
        std::tuple<MDPState *, float> edge_state_reward(edge_state, env.living_reward);
        // go up
        int action = 1;
        std::map<std::tuple<MDPState *, float>, float> state_reward_prob = env.p(edge_state, action);
        REQUIRE(state_reward_prob.size() == 1);
        REQUIRE(state_reward_prob.begin()->first == edge_state_reward);
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }

    SECTION("edge state (1, 1), action: left") {
        MDPState *edge_state = env.get_state_by_coordinates(1, 1);
        std::tuple<MDPState *, float> edge_state_reward(edge_state, env.living_reward);
        // go down
        int action = 3;
        std::map<std::tuple<MDPState *, float>, float> state_reward_prob = env.p(edge_state, action);
        REQUIRE(state_reward_prob.size() == 1);
        REQUIRE(state_reward_prob.begin()->first == edge_state_reward);
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }

    SECTION("edge state (1, 1), action: down") {
        MDPState *edge_state = env.get_state_by_coordinates(1, 1);
        std::tuple<MDPState *, float> edge_state_reward(edge_state, env.living_reward);
        // go down
        int action = 2;
        std::map<std::tuple<MDPState *, float>, float> state_reward_prob = env.p(edge_state, action);
        REQUIRE(state_reward_prob.size() == 1);
        REQUIRE(state_reward_prob.begin()->first == edge_state_reward);
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }

    SECTION("edge state (1, 1), action: up") {
        MDPState *edge_state = env.get_state_by_coordinates(1, 1);
        std::tuple<MDPState *, float> edge_state_reward(edge_state, env.living_reward);
        // go down
        int action = 0;
        std::map<std::tuple<MDPState *, float>, float> state_reward_prob = env.p(edge_state, action);
        REQUIRE(state_reward_prob.size() == 1);
        // next state should be (1, 2) when going up
        MDPState *next_state = env.get_state_by_coordinates(1, 2);
        std::tuple<MDPState *, float> next_state_reward(next_state, env.living_reward);
        REQUIRE(state_reward_prob.begin()->first == next_state_reward);
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }
}

TEST_CASE("Environment Stepping: Deterministic with Obstacles") {
    Environment env = Environment(5, 5, 50, true, -0.01, 10, 0.2);
    // this seed and configuration leads to (4, 3) as start state
    SECTION("Stepping Run") {
        tuple<MDPState *, float, bool> state_reward_bool;
        // step up once
        state_reward_bool = env.step(0);
        REQUIRE(get<1>(state_reward_bool) == env.living_reward);
        REQUIRE(get<2>(state_reward_bool) == false);
        MDPState * current_state = env.get_state_by_coordinates(4, 4);
        REQUIRE(env.current_state == current_state);
        // step down once
        state_reward_bool = env.step(2);
        REQUIRE(get<1>(state_reward_bool) == env.living_reward);
        REQUIRE(get<2>(state_reward_bool) == false);
        current_state = env.get_state_by_coordinates(4, 3);
        REQUIRE(env.current_state == current_state);
        // go left, up, right
        state_reward_bool = env.step(3);
        REQUIRE(get<1>(state_reward_bool) == env.living_reward);
        REQUIRE(get<2>(state_reward_bool) == false);
        state_reward_bool = env.step(0);
        REQUIRE(get<1>(state_reward_bool) == env.living_reward); // deze klopt nog niet
        REQUIRE(get<2>(state_reward_bool) == false);
        state_reward_bool = env.step(1);
        REQUIRE(get<1>(state_reward_bool) == env.living_reward);
        REQUIRE(get<2>(state_reward_bool) == false);
        current_state = env.get_state_by_coordinates(4, 4);
        REQUIRE(env.current_state == current_state);
        // Stepping sequence to the end state
        env.step(3);
        env.step(3);
        state_reward_bool = env.step(2);
        // are in end state: done = true and reward = 10
        REQUIRE(get<1>(state_reward_bool) == env.end_reward);
        REQUIRE(get<2>(state_reward_bool) == true);
    }
}

TEST_CASE("Randomness") {
    Random random(420);
    SECTION("random number") {
        REQUIRE(random.rand() == 434478924);
        REQUIRE(random.random() == 540529033);
        REQUIRE(random.random() == 442346658);
    }
    SECTION("random range") {
        REQUIRE(random.rand(100, 200)==188);
        REQUIRE(random.random_range(100, 200)==104);
    }
    SECTION("random item in any vector") {
        std::vector<int> test_case{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        REQUIRE(random.random_item(test_case)==1);
        REQUIRE(random.random_item(test_case)==9);
        REQUIRE(random.random_item(test_case)==2);
    }
}


TEST_CASE("State getters and setters") {
    std::vector<int> actions{0, 1, 2, 3};
    State state(0, 0, actions);
    REQUIRE(state.getCoordinates() == std::make_pair(0,0));
    REQUIRE(state.getValue(0)==0);
    REQUIRE(state.getActionCount(1)==0);
    state.incrementCounter(1);
    REQUIRE(state.getActionCount(1)==1);
    state.resetCounter();
    REQUIRE(state.getActionCount(1)==0);
}

TEST_CASE("Learning automata tests") {
    std::vector<int> actions{0, 1, 2, 3};
    std::pair<int,int> start_coordinates{0,0};
    LA la(2, 2, start_coordinates, actions);
    SECTION("start state"){
        REQUIRE(la.getStartState()->getCoordinates() == start_coordinates);
    }
    SECTION("argmax") {
        State* state = la.getStartState();
        state->setValue(0, 1);
        REQUIRE(la.argmax(state)==0);
        state->setValue(1, 2);
        REQUIRE(la.argmax(state)==1);
    }
    SECTION("coordinates to state") {
        REQUIRE(la.coordinatesToState(std::make_tuple(1, 1))->getCoordinates()==std::make_pair(1,1));
    }
    SECTION("default constructor") {
        LA la2;
        REQUIRE(la2.isProperlyInitialized()==false);
        REQUIRE(la.isProperlyInitialized()==true);
    }
}

TEST_CASE("QLearning Tests") {
    Environment env = Environment(10, 10, 42, true, -0.01, 10, 0.2);
    QLearning ql = QLearning(&env,0.1, 0.01, 0.9);
    ql.train(&env, 2000, 50, 10);
    // todo write a test once we have an optimal path algorithm
}

TEST_CASE("MCLearning tests") {
    std::vector<int> actions{0, 1, 2, 3};

    Environment env = Environment(5, 5, 42, true, -0.01, 10, 0.2);
    LA la(5, 5, std::make_pair(env.start->x, env.start->y), actions);
    MCLearning agent(la, 0.9);
    agent.play(env, 200);
    SECTION("episode test") {
        auto episode = agent.play(env, 200);
        REQUIRE(episode.empty()==false);
    }
}

TEST_CASE("Non deterministic enviroment") {
    Environment env = Environment(5, 5, 42, false, -0.01, 10, 0.2);
    env.render();
    REQUIRE(env.deterministic == false);
    REQUIRE(env.get_state_by_coordinates(2,2)->symbol == "w");
    // test if there is a non-1 probability
    REQUIRE((env.p(env.get_state_by_coordinates(2,2), 0).begin()->second)!=1);
    // test if there are more that one resulting state in the dynamics
    REQUIRE((env.p(env.get_state_by_coordinates(4,2), 2).size())!=1);
}
