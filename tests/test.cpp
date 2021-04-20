#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../datastructures/Environment.h"

TEST_CASE("Environment Basics"){
    Environment env = Environment(10, 5, 42, true, -0.01, 0.2);
    REQUIRE(env.height == 10);
    REQUIRE(env.width == 5);
    REQUIRE(env.start != env.end);
    REQUIRE(env.observable_states.size() == 50);
}

TEST_CASE("Environment Generation: Deterministic without Obstacles"){
    Environment env = Environment(10, 5, 42, true,-0.01, 0.0);
    SECTION("edge state (0, 0), action: left"){
        std::tuple<int, int> edge_state (0, 0);
        std::tuple<std::tuple<int, int>, float> edge_state_reward (edge_state, env.living_reward);
        // go to the left
        int action = 3;
        std::map <std::tuple<std::tuple<int, int>, float>, float> state_reward_prob = env.p(edge_state, action);
        // can only be one next state since it's a deterministic environment
        REQUIRE(state_reward_prob.size() == 1);
        // the next state should be the current state
        REQUIRE(state_reward_prob.begin()->first == edge_state_reward);
        // probability should be 100% (deterministic)
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }

    SECTION("edge state (0, 0), action: up"){
        std::tuple<int, int> edge_state (0, 0);
        std::tuple<std::tuple<int, int>, float> edge_state_reward (edge_state, env.living_reward);
        // go up
        int action = 0;
        std::map <std::tuple<std::tuple<int, int>, float>, float> state_reward_prob = env.p(edge_state, action);
        // can only be one next state since it's a deterministic environment
        REQUIRE(state_reward_prob.size() == 1);
        // next state should be (0, 1) when going up
        std::tuple<int, int> next_state (0, 1);
        std::tuple<std::tuple<int, int>, float> next_state_reward (next_state, env.living_reward);
        REQUIRE(state_reward_prob.begin()->first == next_state_reward);
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }

    SECTION("edge state (4, 9), action: up"){
        std::tuple<int, int> edge_state (4, 9);
        std::tuple<std::tuple<int, int>, float> edge_state_reward (edge_state, env.living_reward);
        // go up
        int action = 0;
        std::map <std::tuple<std::tuple<int, int>, float>, float> state_reward_prob = env.p(edge_state, action);
        REQUIRE(state_reward_prob.size() == 1);
        // the next state should be the current state
        REQUIRE(state_reward_prob.begin()->first == edge_state_reward);
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }


    SECTION("edge state (4, 9), action: down"){
        std::tuple<int, int> edge_state (4, 9);
        std::tuple<std::tuple<int, int>, float> edge_state_reward (edge_state, env.living_reward);
        // go down
        int action = 2;
        std::map <std::tuple<std::tuple<int, int>, float>, float> state_reward_prob = env.p(edge_state, action);
        REQUIRE(state_reward_prob.size() == 1);
        // next state should be (4, 8) when going down
        std::tuple<int, int> next_state (4, 8);
        std::tuple<std::tuple<int, int>, float> next_state_reward (next_state, env.living_reward);
        REQUIRE(state_reward_prob.begin()->first == next_state_reward);
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }

    SECTION("edge state (4, 9), action: right"){
        std::tuple<int, int> edge_state (4, 9);
        std::tuple<std::tuple<int, int>, float> edge_state_reward (edge_state, env.living_reward);
        // go right
        int action = 1;
        std::map <std::tuple<std::tuple<int, int>, float>, float> state_reward_prob = env.p(edge_state, action);
        REQUIRE(state_reward_prob.size() == 1);
        // the next state should be the current state
        REQUIRE(state_reward_prob.begin()->first == edge_state_reward);
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }
}

TEST_CASE("Environment Generation: Deterministic with Obstacles"){
    Environment env = Environment(5, 2, 42, true,-0.01, 0.2);
    // this seed and configuration leads to (1, 0) and (0, 1) being chosen as obstacles
    // todo this result will change when we implement the path checking!
    SECTION("edge state (0, 0), action: up"){
        std::tuple<int, int> edge_state (0, 0);
        std::tuple<std::tuple<int, int>, float> edge_state_reward (edge_state, env.living_reward);
        // go up
        int action = 0;
        std::map <std::tuple<std::tuple<int, int>, float>, float> state_reward_prob = env.p(edge_state, action);
        REQUIRE(state_reward_prob.size() == 1);
        // the next state should be the current state
        REQUIRE(state_reward_prob.begin()->first == edge_state_reward);
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }
}

